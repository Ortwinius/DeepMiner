#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "common.h"
#include "robot.h"
#include "starsweeper.h"
#include "earthcrusher.h"
#include "voidifier.h"

typedef std::vector<std::vector<std::vector<Block>>> WorldGrid;
typedef std::vector<std::vector<Block>> WorldGridColumn;

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
	WorldGrid worldGrid; // TODO : throw on the heap?

	int getColumnHeight(int x, int y);
	std::vector<Block> getColumn(const Vec3& pos);
	void setColumn(const std::vector<Block>& newColumn, const Vec3& pos);
	void printRobotColumnValues(const Vec3& robotColumn);
	std::random_device rd; 
	std::mt19937 gen; 
};