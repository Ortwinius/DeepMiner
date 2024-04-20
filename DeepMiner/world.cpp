#include "world.h"

World::World()
{
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
	std::vector<std::vector<std::vector<int>>> worldGrid
		(WorldDimensions::dimX, std::vector<std::vector<int>>
			(WorldDimensions::dimY, std::vector<int>(WorldDimensions::dimZ)));


}

void World::updateWorld(const Direction& movementDirection)
{
	player->move(left);
	player->move(left);
	player->move(right);
}

void World::renderWorld()
{
	for (int y = 0; y < WorldDimensions::dimY; y++)
	{
		for (int x = 0; x < WorldDimensions::dimX; x++)
		{
			// draw to the screen
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
