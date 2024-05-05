#include "world.h"

World::World()
	: rd()
	, gen(rd())
{
	srand(time(0));
	initWorld();
}

World::~World()
{
	for (auto robot : robots)
	{
		delete robot;
	}
}

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

	// get and set player class
	bool playerValidated = false;
	while (!playerValidated)
	{
		char robotChoice;
		std::cout << "Choose your robot type: " <<
			std::endl << "1 - StarSweeper" <<
			std::endl << "2 - EarthCrusher" <<
			std::endl << "3 - Voidifier" << std::endl;

		std::cin >> robotChoice;
		switch (robotChoice)
		{
		case '1':
			std::cout << "Player chooses StarSweeper class" << std::endl;
			player = new StarSweeper(false);
			playerValidated = true;
			break;
		case '2':
			std::cout << "Player chooses EarthCrusher class" << std::endl;
			player = new EarthCrusher(false);
			playerValidated = true;
			break;
		case '3':
			std::cout << "Player chooses Voidifier class" << std::endl;
			player = new Voidifier(false);
			playerValidated = true;
			break;
		default:
			std::cout << "Please choose a valid robot type" << std::endl;
			break;
		}
	}

	// add player to entity vector
	robots.push_back(player);

	/*for (int i = 0; i < DefaultValues::aiRobotCount; i++)
	{
		int robotType = generateRandomNumber(gen, 1, 3);

		switch (robotType)
		{
		case 1:
			std::cout << "Robot " << i+1 << " chooses StarSweeper class " << std::endl;
			robots.push_back(new StarSweeper(true));
			break;		
		case 2:
			std::cout << "Robot " << i << " chooses EarthCrusher class " << std::endl;
			robots.push_back(new EarthCrusher(true));
			break;
		case 3:
			std::cout << "Robot " << i << " chooses Voidifier class " << std::endl;
			robots.push_back(new Voidifier(true));
			break;
		default:
			break;
		}
	}*/
}

void World::updateWorld(const Direction& movementDirection)
{

	player->move(movementDirection);
	printRobotColumnValues(player->getPosition());
	player->mine();

	// for AI robots -> randomized movement behaviour
	for (auto robot : robots)
	{
		if (robot->isAI())
		{
			robot->move(static_cast<Direction>(generateRandomNumber(gen, 0,4)));
			robot->mine();
		}
	}
}

void World::renderWorld()
{
	std::cout << std::endl;
	for (int y = 0; y < WorldDimensions::dimY; y++)
	{
		for (int x = 0; x < WorldDimensions::dimX; x++)
		{
			// calculate highest z-value not equal to air 
			int columnHeight = getColumnHeight(x,y) - 1;
			Vec3 currentPos = Vec3(x, y, columnHeight);
			bool isRobot = false;

			// if there is a robot on the highest field -> draw it, else draw the block
			for (const auto& robot : robots)
			{
				if (robot->getPosition() == currentPos)
				{
					std::cout << "R ";
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

void World::printRobotColumnValues(const Vec3& robotColumn)
{
	int x = robotColumn.x;
	int y = robotColumn.y;

	std::cout << "Column [" << x << "] [" << y << "] Z values: " << std::endl;

	// descending order
	for (int z = WorldDimensions::dimZ - 1; z << WorldDimensions::dimZ >= 0; z--)
	{
		std::cout << "Z [" << z << "]: " << convertBlockToChar(worldGrid[x][y][z].getBlockType()) << std::endl;
	}
}


