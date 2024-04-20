#pragma once

#include <iostream>
#include <vector>
#include "robot.h"
#include "starsweeper.h"

class World
{
public:
	World();
	~World();

	void initWorld();
	void updateWorld(const Direction& movementDirection);
	void renderWorld();
private:
	Robot* player;
	std::vector<Robot*> robots;
	std::vector<std::vector<std::vector<int>>> worldGrid;
};