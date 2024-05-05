#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "common.h"
#include "robot.h"
#include "starsweeper.h"
#include "earthcrusher.h"
#include "voidifier.h"

class World
{
public:
	World();
	~World();

	void initWorld();
	void updateWorld(const Direction& movementDirection);
	void renderWorld();

	const Robot* getPlayerRef() const { return player; }

private:
	Robot* player;
	std::vector<Robot*> robots;
	std::vector<std::vector<std::vector<Block>>> worldGrid;

	int getColumnHeight(int x, int y);
	void printRobotColumnValues(const Vec3& robotColumn);
	std::random_device rd; 
	std::mt19937 gen; 
};