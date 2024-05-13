#include "world.h"

World::World(int robotCount)
	: rd()
	, gen(rd())
{
	srand(time(0));
	initWorld(robotCount);
}

World::~World()
{}

void World::initWorld(int robotCount)
{	
	// clear and init worldgrid vector to 5*5*10
	world.clear();
	world.resize(WorldDimensions::dimX, std::vector<std::vector<Block>>
		(WorldDimensions::dimY, std::vector<Block>(WorldDimensions::dimZ)));

	// create random blocks with gen-randomizer 
	for (int z = 0; z < WorldDimensions::dimZ; z++)
	{
		for (int y = 0; y < WorldDimensions::dimY; y++)
		{
			for (int x = 0; x < WorldDimensions::dimX; x++)
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

void World::updateWorld()
{
	// AI robots -> randomized movement behaviour
	for (auto& robot : robots)
	{
		if (robot->isAlive())
		{
			robot->move(world, gen);
			robot->mine(getColumn(robot->getPosition()));

			// update column with new values
			Vec3 robotPos = robot->getPosition();
			setColumn(getColumn(robotPos), robotPos);
		}
		else
		{
			// remove dead robots
			robots.erase(std::remove(robots.begin(), robots.end(), robot), robots.end());
		}
	}
	checkWorldEmpty();
}

void World::renderWorld()
{
	std::cout << std::endl;
	for (int y = 0; y < WorldDimensions::dimY; y++)
	{
		for (int x = 0; x < WorldDimensions::dimX; x++)
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
				if (robot->getPosition().x == currentPos.x && robot->getPosition().y == currentPos.y)
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

int World::getColumnHeight(int x, int y)
{
	int h = 0;
	for (int z = 0; z < WorldDimensions::dimZ; z++)
	{
		if (world[x][y][z].getBlockType() != BlockType::air)
			h++;
	}
	return h;
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

	while (z < WorldDimensions::dimZ)
	{
		world[pos.x][pos.y][z] = newColumn[z];
		z++;
	}
}

void World::printRobotColumnValues(const Vec3& robotColumn)
{
	std::cout << "Column [" << robotColumn.x << "] [" << robotColumn.y << "] Z values: " << std::endl;

	// descending order
	for (int z = WorldDimensions::dimZ - 1; z >= 0; z--)
	{
		std::cout << "Z [" << z << "]: " << convertBlockToChar(world[robotColumn.x][robotColumn.y][z].getBlockType()) << std::endl;
	}
}

const bool World::checkWorldEmpty()
{
	// check if the whole world grid is air
	for(int z = 0; z < WorldDimensions::dimZ; z++)
	{
		for(int y = 0; y < WorldDimensions::dimY; y++)
		{
			for(int x = 0; x < WorldDimensions::dimX; x++)
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
	for (int z = 0; z < WorldDimensions::dimZ; z++)
	{
		for (int y = 0; y < WorldDimensions::dimY; y++)
		{
			for (int x = 0; x < WorldDimensions::dimX; x++)
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


