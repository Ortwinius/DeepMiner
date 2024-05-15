#include "world.h"

World::World(int robotCount)
	: rd()
	, gen(rd())
	, totalMinableScore(0)
{
	srand(time(0));
	initWorld();
	initRobots(robotCount);
}

World::~World() = default;

void World::initWorld()
{	
	// clear and init worldgrid vector to 5*5*10
	this->worldGrid.clear();
	this->worldGrid.resize(dimX, std::vector<std::vector<Block>>
		(dimY, std::vector<Block>(dimZ)));

	// create random blocks with gen-randomizer 
	for (int z = 0; z < dimZ; z++)
	{
		for (int y = 0; y < dimY; y++)
		{
			for (int x = 0; x < dimX; x++)
			{
				this->worldGrid[x][y][z] = Block(gen);
			}
		}
	}
	this->totalMinableScore = calculateTotalMinableScore();
}

// create robots randomly and add them to robots vector
void World::initRobots(int robotCount)
{
	for (int i = 0; i < robotCount; i++)
	{
		const std::string name = "M_" + std::to_string(i + 1);
		int robotClass = generateRandomNumber(gen, 1, DefaultValues::robotClassCount);

		switch (robotClass)
		{
		case 1:
		{
			this->robots.push_back(std::make_unique<StarSweeper>(name));
			break;
		}
		case 2:
		{
			this->robots.push_back(std::make_unique<EarthCrusher>(name));
			break;
		}
		case 3:
		{
			this->robots.push_back(std::make_unique<Voidifier>(name));
			break;
		}
		default:
			break;
		}
	}
}

// run all robot threads in parallel by reserving one thread for each robot
void World::runRobotThreads()
{
	// reserve space for all robots
	this->robotThreads.reserve(robots.size());

	// run robots in parallel
	for (auto& robot : robots)
	{
		this->robotThreads.push_back(std::thread(&World::runRobot, this, std::ref(robot)));
	}

	for (auto& thread : this->robotThreads) 
	{
		thread.join();
	}
}

// running one robot thread until he is dead or the world is empty
// lock the column mutex before updating it (in robot->mine) so that no other robot can access it
void World::runRobot(std::unique_ptr<Robot>& robot)
{
	auto startTime = Timer::now();

	while (robot->isAlive() && !checkWorldEmpty())
	{
		robot->move(this->worldGrid, this->gen);

		performAttack(robot);

		std::lock_guard<std::mutex> lock(this->columnMutexes[robot->getPos().x][robot->getPos().y]);
		robot->mine(getColumn(robot->getPos()));
	}

	auto endTime = Timer::now();
	robot->setThreadExecutionTime(calculateDeltaTime(startTime, endTime)); // save thread execution time in robot	
}

// getter for world grid column
std::vector<Block>& World::getColumn(const Vec3& pos)
{
	std::vector<Block>& col = worldGrid[pos.x][pos.y];
	return col;
}

// get all robots on the same and adjacent fields and attack them
void World::performAttack(std::unique_ptr<Robot>& robot)
{
	if(!robot->isAlive()) return;

	for (Direction dir = Direction::idle; dir < Direction::right; dir = static_cast<Direction>(static_cast<int>(dir) + 1))
	{
		Vec3 newPos = robot->getPos() + robot->getDirectionVec(dir);
		std::set<Robot*> robots = getRobotsOnColumn(newPos);
		robots.erase(robot.get()); // exclude current robot from attack to prevent self-attack

		// attack all robots on the same column
		for (auto& other : robots)
		{
			if (other->isAlive() && (robot->getPos().z == other->getPos().z))
			{
				robot->attackRobot(*other);
			}
		}
	}
}

// return alive robots on the same column
std::set<Robot*> World::getRobotsOnColumn(const Vec3& pos)
{
	std::set<Robot*> robotSet;
	for (auto& robot : robots)
	{
		if (robot->isAlive() && robot->getPos().x == pos.x && robot->getPos().y == pos.y)
		{
			robotSet.insert(robot.get());
		}
	}
	return robotSet;
}

int World::getColumnHeight(int x, int y)
{
	int h = 0;
	for (int z = 0; z < dimZ; z++)
	{
		if (this->worldGrid[x][y][z].getBlockType() != BlockType::air)
			h++;
	}
	return h;
}

void World::printRobotColumnValues(const Vec3& robotColumn)
{
	std::cout << "Column [" << robotColumn.x << "] [" << robotColumn.y << "] Z values: " << std::endl;

	// descending order
	for (int z = dimZ - 1; z >= 0; z--)
	{
		std::cout << "Z [" << z << "]: " << convertBlockToChar(worldGrid[robotColumn.x][robotColumn.y][z].getBlockType()) << std::endl;
	}
}

const bool World::checkWorldEmpty()
{
	// check if the whole world grid is air
	for(int z = 0; z < dimZ; z++)
	{
		for(int y = 0; y < dimY; y++)
		{
			for(int x = 0; x < dimX; x++)
			{
				if(worldGrid[x][y][z].getBlockType() != BlockType::air)
				{
					return false;
				}
			}
		}
	}
	return true;
}

int World::calculateTotalMinableScore()
{
	int score = 0;
	for (int z = 0; z < dimZ; z++)
	{
		for (int y = 0; y < dimY; y++)
		{
			for (int x = 0; x < dimX; x++)
			{
				score += convertBlockTypeToScoreValue(this->worldGrid[x][y][z].getBlockType());
			}
		}
	}

	return score;
}

int World::getTotalRobotScore()
{
	int score = 0;
	for(auto &robot : this->robots)
	{
		score += robot->getScore();
	}
	return score;
}

// NOTE: not used for parallel deep miner implementation
void World::renderWorld()
{
	std::cout << std::endl;
	for (int y = 0; y < dimY; y++)
	{
		for (int x = 0; x < dimX; x++)
		{
			// calculate highest z-value not equal to air (subtract one for index)
			int columnHeight = getColumnHeight(x, y);
			if (columnHeight > 0)
			{
				columnHeight--;
			}

			Vec3 currentPos = Vec3(x, y, columnHeight);
			bool isRobot = false;

			// if there is a robot on the highest field -> draw it, else draw the block
			for (const auto& robot : this->robots)
			{
				if (robot->getPos().x == currentPos.x && robot->getPos().y == currentPos.y)
				{
					std::cout << "Ü ";
					isRobot = true;
					break;
				}
			}
			// else print the highest z-value
			if (!isRobot)
			{
				std::cout << convertBlockToChar(this->worldGrid[x][y][columnHeight].getBlockType()) << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

