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
	// get and set player class
	bool playerValidated = false;
	while (!playerValidated)
	{
		char robotChoice;
		std::cout << "Choose your robot type (1 - StarSweeper, ...):" << std::endl;
		std::cin >> robotChoice;
		switch (robotChoice)
		{
		case '1':
			std::cout << "StarSweeper class chosen" << std::endl;
			player = new StarSweeper();
			playerValidated = true;
			break;
		default:
			std::cout << "Please choose a valid robot type" << std::endl;
			break;
		}
	}
	// add player to entity vector
	robots.push_back(player);
	
	// clear and init worldgrid vector to 5*5*10
	worldGrid.clear();
	worldGrid.resize(WorldDimensions::dimX, std::vector<std::vector<Block>>
		(WorldDimensions::dimY, std::vector<Block>(WorldDimensions::dimZ)));

	for (int z = 0; z < WorldDimensions::dimZ; z++)
	{
		for (int y = 0; y < WorldDimensions::dimY; y++)
		{
			for (int x = 0; x < WorldDimensions::dimX; x++)
			{
				// create random blocks with gen-randomizer
				worldGrid[x][y][z] = Block(gen);
			}
		}
	}

}

void World::updateWorld(const Direction& movementDirection)
{
	player->move(movementDirection);
	for (auto robot : robots)
	{
		if (robot->isAI())
		{
			robot->move(static_cast<Direction>(generateRandomNumber(gen, 0,4)));
		}
	}
}

void World::renderWorld()
{
	for (int y = 0; y < WorldDimensions::dimY; y++)
	{
		for (int x = 0; x < WorldDimensions::dimX; x++)
		{
			// draw to the screen

			std::cout << convertBlockToChar(worldGrid[x][y][DefaultValues::startingHeight].getBlockType()) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


