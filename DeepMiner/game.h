#pragma once
#include <memory>
#include <chrono>
#include "world.h"
#include "constants.h"
#include "robot.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	typedef std::chrono::high_resolution_clock Timer;

	bool isRunning = false;
	std::unique_ptr<World> world;

	int validateRobotCount();
	void initGame();
	void showRobotScores(const std::vector<std::unique_ptr<Robot>>& robots);
	void showTotalRobotScore(int score);
	void showTotalMinableScore(int score);
	void showTotalExecutionTime(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> end);
	
};