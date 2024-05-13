#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <thread>
#include <mutex>
#include "common.h"
#include "robot.h"
#include "starsweeper.h"
#include "earthcrusher.h"
#include "voidifier.h"

using namespace WorldDimensions; // for better readability (dimX, dimY, dimZ)

class World
{
public:
	World(int robotCount);
	~World();

	void initWorld(int robotCount);
	void runThreads();
	void renderWorld();

	const std::vector<std::unique_ptr<Robot>>& getRobots() const { return robots; }
	const bool checkWorldEmpty();
	int getTotalMinableScore();
	int getTotalRobotScore();

private:
	typedef std::vector<std::vector<std::vector<Block>>> WorldGrid;
	typedef std::mt19937 RandGen;

	WorldGrid world; 
	std::vector<std::unique_ptr<Robot>> robots;
	std::vector<std::thread> robotThreads;
	std::mutex columnMutexes[dimX][dimY];
	std::random_device rd;
	RandGen gen;

	void runRobot(std::unique_ptr<Robot>& robot);
	std::vector<Block>& getColumn(const Vec3& pos);
	void setColumn(const std::vector<Block>& newColumn, const Vec3& pos);
	int getColumnHeight(int x, int y);
	void printRobotColumnValues(const Vec3& robotColumn);
};