#include "world.h"

World::World()
	: rd()
	, gen(rd())
{
	srand(time(0));
	initWorld();
}

int World::iterationCounter = 0;

World::~World()
{}

void World::initWorld()
{	
	// clear and init worldgrid vector to 5*5*10
	worldGrid.clear();
	worldGrid.resize(WorldDimensions::dimX, std::vector<std::vector<Block>>
		(WorldDimensions::dimY, std::vector<Block>(WorldDimensions::dimZ)));

	// create random blocks with gen-randomizer 
	for (int z = 0; z < WorldDimensions::dimZ; z++)
	{
		for (int y = 0; y < WorldDimensions::dimY; y++)
		{
			for (int x = 0; x < WorldDimensions::dimX; x++)
			{
				worldGrid[x][y][z] = Block(gen);
			}
		}
	}

	// ask user for how many robots to spawn and then validate input for x robots
	int robotCount = 0;
	std::cout << "How many robots do you want to spawn? (1 - 6)" << std::endl;
	std::cin >> robotCount;

	while (std::cin.fail() || robotCount < 0 || robotCount > 6)
	{
		std::cout << "Please enter a valid number between 1 and 6" << std::endl;
		std::cin.clear();
		std::cin.ignore(128, '\n');
		std::cin >> robotCount;
	}

	// create robots and add them to robots vector
	
	for(int i = 0; i < robotCount; i++)
	{
		int robotClass = generateRandomNumber(gen, 0, 2);
		switch (robotClass)
		{
		case 0:
			{
				std::cout << "EarthCrusher spawned..." << std::endl;
				robots.push_back(std::make_unique<EarthCrusher>(true));
				break;
			}
		case 1:
			{
				std::cout << "Voidifier spawned..." << std::endl;
				robots.push_back(std::make_unique<Voidifier>(true));
				break;
			}
		case 2:
			{
				std::cout << "Voidifier spawned..." << std::endl;
				robots.push_back(std::make_unique<Voidifier>(true));
				break;
			}
		}
	}
	// 
	//robots.push_back(std::make_unique<EarthCrusher>(true));
}

void World::updateWorld()
{
	// AI robots -> randomized movement behaviour
	for (auto& robot : robots)
	{
		robot->move(static_cast<Direction>(generateRandomNumber(gen, 0,4)));

		std::vector<Block> robotColumn = getColumn(robot->getPosition());
		robot->updateRobotHeight(robotColumn);
		robot->mine(robotColumn);
		robot->updateRobotHeight(robotColumn);
		setColumn(robotColumn, robot->getPosition());

		printRobotColumnValues(robot->getPosition());
	}
	checkWorldEmpty();

	//iterationCounter++;
	//if (iterationCounter > 200)
	//{
	//	exit(0);
	//}
	// 
	// 
	//auto moveMineUpdate = [&](std::unique_ptr<Robot>& robot, Direction direction) {
	//	robot->move(direction);
	//	std::vector<Block> robotColumn = getColumn(robot->getPosition());
	//	robot->updateRobotHeight(robotColumn);
	//	robot->mine(robotColumn);
	//	robot->updateRobotHeight(robotColumn);
	//	setColumn(robotColumn, robot->getPosition());

	//	printRobotColumnValues(robot->getPosition());
	//};

	//for (auto& robot : robots)
	//{
	//	moveMineUpdate(robot, Direction::idle);		
	//	moveMineUpdate(robot, Direction::idle);		
	//	moveMineUpdate(robot, Direction::idle);		
	//	moveMineUpdate(robot, Direction::idle);
	//	moveMineUpdate(robot, Direction::forward);
	//	moveMineUpdate(robot, Direction::backward);
	//	moveMineUpdate(robot, Direction::left);
	//	moveMineUpdate(robot, Direction::right);
	//}
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
				std::cout << convertBlockToChar(worldGrid[x][y][columnHeight].getBlockType()) << " ";
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
		if (worldGrid[x][y][z].getBlockType() != BlockType::air)
			h++;
	}
	return h;
}

// set world grid column at pos XY to values of newColumn
void World::setColumn(const std::vector<Block>& newColumn, const Vec3& pos)
{
	int z = 0;

	while (z < WorldDimensions::dimZ)
	{
		worldGrid[pos.x][pos.y][z] = newColumn[z];
		z++;
	}
}

// returns reference on worldGrid column
std::vector<Block> World::getColumn(const Vec3& pos)
{
	std::vector<Block> col = {};
	int z = 0;

	while (z < WorldDimensions::dimZ)
	{
		col.push_back(worldGrid[pos.x][pos.y][z]);
		z++;
	}

	return col;
}

void World::printRobotColumnValues(const Vec3& robotColumn)
{
	std::cout << "Column [" << robotColumn.x << "] [" << robotColumn.y << "] Z values: " << std::endl;

	// descending order
	for (int z = WorldDimensions::dimZ - 1; z >= 0; z--)
	{
		std::cout << "Z [" << z << "]: " << convertBlockToChar(worldGrid[robotColumn.x][robotColumn.y][z].getBlockType()) << std::endl;
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
				if(worldGrid[x][y][z].getBlockType() != BlockType::air)
				{
					return false;
				}
			}
		}
	}
	return true;
}


