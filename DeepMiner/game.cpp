#include "game.h"

Game::Game()
{
	initGame();
}

Game::~Game() = default;

int Game::validateRobotCount()
{
	// ask user for how many robots to spawn and then validate input for x robots
	int robotCount = 0;
	std::cout << "How many robots do you want to spawn? (" << DefaultValues::minRobotCount << " - " << DefaultValues::maxRobotCount << ")" << std::endl;
	std::cin >> robotCount;

	while (std::cin.fail() 
		|| robotCount < DefaultValues::minRobotCount
			|| robotCount > DefaultValues::maxRobotCount)
	{
		std::cout << "Please enter a valid number between " << DefaultValues::minRobotCount << " and " << DefaultValues::maxRobotCount << std::endl;
		std::cin.clear();
		std::cin.ignore(128, '\n');
		std::cin >> robotCount;
	}

	return robotCount;
}

void Game::initGame()
{
	isRunning = true;
	int robotCount = validateRobotCount();
	world = std::make_unique<World>(robotCount);
}

void Game::run()
{
	// show total minable score
	showTotalMinableScore(world->getTotalMinableScore());

	// main "game loop" without handleInput and render for parallel deep miner implementation
	auto startTime = Timer::now();
	world->runRobotThreads();
	auto endTime = Timer::now();

	// show final score
	showRobotStats(world->getRobots());
	showTotalExecutionTime(startTime, endTime);
	showTotalMinableScore(world->getTotalMinableScore());
	showTotalRobotScore(world->getTotalRobotScore());
}

void Game::showTotalRobotScore(int score)
{
	std::cout << "Total sum of robot scores: " << score << std::endl;
}

void Game::showTotalMinableScore(int score)
{
	std::cout << "Total sum of possible minable score points: " << score << std::endl;
}

void Game::showTotalExecutionTime(std::chrono::time_point<std::chrono::high_resolution_clock> startTime, std::chrono::time_point<std::chrono::high_resolution_clock> endTime)
{
	std::cout << "Total execution time: " << calculateDeltaTime(startTime, endTime) << " ms" << std::endl;
}

void Game::showRobotStats(const std::vector<std::unique_ptr<Robot>>& robots)
{
	for (auto& robot : robots)
	{
		robot->getRobotStats();
	}
}
