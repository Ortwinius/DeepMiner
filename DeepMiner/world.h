#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <chrono>
#include <iomanip>
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

	void runRobotThreads();
	void renderWorld();
	const std::vector<std::unique_ptr<Robot>>& getRobots() const { return robots; }
	const int getTotalMinableScore() { return totalMinableScore; }
	int getTotalRobotScore();

private:
	typedef std::vector<std::vector<std::vector<Block>>> WorldGrid;
	typedef std::mt19937 RandGen;
	typedef std::chrono::high_resolution_clock Timer;

	WorldGrid world; 
	std::vector<std::unique_ptr<Robot>> robots;
	std::vector<std::thread> robotThreads;
	std::mutex columnMutexes[dimX][dimY];
	std::random_device rd;
	RandGen gen;
	int totalMinableScore;

	void initWorld();
	void initRobots(int robotCount);
	int calculateTotalMinableScore();
	const bool checkWorldEmpty();
	void runRobot(std::unique_ptr<Robot>& robot);
	std::vector<Block>& getColumn(const Vec3& pos);
	void performAttack(std::unique_ptr<Robot>& robot);
	std::set<Robot*> getRobotsOnColumn(const Vec3& pos);
	int getColumnHeight(int x, int y);
	void printRobotColumnValues(const Vec3& robotColumn);
};