#include "world.h"

World::World()
{
	player = new StarSweeper();
	init();
}

World::~World()
{
	if (player != nullptr)
	{
		delete player;
	}
}

void World::init()
{
	player->move(left);
	player->move(left);
	player->move(right);
}
