#include "world.h"

World::World(int robotCount)
	: rd()
	, gen(rd())
{
	srand(time(0));
	initWorld(robotCount);
}

World::~World() = default;

void World::initWorld(int robotCount)
{	
	// clear and init worldgrid vector to 5*5*10
	world.clear();
	world.resize(dimX, std::vector<std::vector<Block>>
		(dimY, std::vector<Block>(dimZ)));

	// create random blocks with gen-randomizer 
	for (int z = 0; z < dimZ; z++)
	{
		for (int y = 0; y < dimY; y++)
		{
			for (int x = 0; x < dimX; x++)
			{
				world[x][y][z] = Block(gen);
			}
		}
	}

	// create robots and add them to robots vector
	
	for(int i = 0; i < robotCount; i++)
	{
		int robotClass = generateRandomNumber(gen, 1, DefaultValues::robotClassCount);

		switch (robotClass)
		{
		case 1:
			{
				robots.push_back(std::make_unique<StarSweeper>());
				break;
			}
		case 2:
			{
				robots.push_back(std::make_unique<EarthCrusher>());
				break;
			}
		case 3:
			{
				robots.push_back(std::make_unique<Voidifier>());
				break;
			}
		default:
			break;
		}
	}
}

void World::runThreads()
{
	// reserve space for all robots
	robotThreads.reserve(robots.size());

	// run robots in parallel
	for (auto& robot : robots)
	{
		robotThreads.push_back(std::thread(&World::runRobot, this, std::ref(robot)));
	}

	for (auto& thread : robotThreads) {
		thread.join();
	}
}

void World::runRobot(std::unique_ptr<Robot>& robot)
{
	while (robot->isAlive() && !checkWorldEmpty())
	{
		robot->move(world, gen);
		// lock the column mutex before updating it so that no other robot can access it
		std::lock_guard<std::mutex> lock(columnMutexes[robot->getPos().x][robot->getPos().y]);

		robot->mine(getColumn(robot->getPos()));

		// update column with new values
		setColumn(getColumn(robot->getPos()), robot->getPos());
	}
}

// getter for world grid column
std::vector<Block>& World::getColumn(const Vec3& pos)
{
	std::vector<Block>& col = world[pos.x][pos.y];
	return col;
}

// set world grid column at pos XY to values of newColumn
void World::setColumn(const std::vector<Block>& newColumn, const Vec3& pos)
{
	int z = 0;

	while (z < dimZ)
	{
		world[pos.x][pos.y][z] = newColumn[z];
		z++;
	}
}

int World::getColumnHeight(int x, int y)
{
	int h = 0;
	for (int z = 0; z < dimZ; z++)
	{
		if (world[x][y][z].getBlockType() != BlockType::air)
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
		std::cout << "Z [" << z << "]: " << convertBlockToChar(world[robotColumn.x][robotColumn.y][z].getBlockType()) << std::endl;
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
				if(world[x][y][z].getBlockType() != BlockType::air)
				{
					return false;
				}
			}
		}
	}
	return true;
}

int World::getTotalMinableScore()
{
	int score = 0;
	for (int z = 0; z < dimZ; z++)
	{
		for (int y = 0; y < dimY; y++)
		{
			for (int x = 0; x < dimX; x++)
			{
				score += convertBlockTypeToScoreValue(world[x][y][z].getBlockType());
			}
		}
	}

	return score;
}

int World::getTotalRobotScore()
{
	int score = 0;
	for(auto &robot : robots)
	{
		score += robot->getScore();
	}
	return score;
}

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
			for (const auto& robot : robots)
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
				std::cout << convertBlockToChar(world[x][y][columnHeight].getBlockType()) << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

