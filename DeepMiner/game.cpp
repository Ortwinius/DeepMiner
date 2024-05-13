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
	showTotalMinableScore(world->getTotalMinableScore());

	// main game loop without handleInput and render because of automated parallelized flow
	auto startTime = Timer::now();
	world->runThreads();
	auto endTime = Timer::now();

	// show final score
	showTotalRobotScore(world->getTotalRobotScore());
	showTotalExecutionTime(startTime, endTime);
}

void Game::showRobotScores(const std::vector<std::unique_ptr<Robot>>& robots)
{
	int i = 1;
	for (auto& robot : robots)
	{
		std::cout << "Robot " << i << " score: " << robot->getScore() << std::endl;
		i++;
	}
}

void Game::showTotalRobotScore(int score)
{
	std::cout << "Total sum of robot scores: " << score << std::endl;
}

void Game::showTotalMinableScore(int score)
{
	std::cout << "Total sum of minable score points: " << score << std::endl;
}

void Game::showTotalExecutionTime(std::chrono::time_point<std::chrono::high_resolution_clock> startTime, std::chrono::time_point<std::chrono::high_resolution_clock> endTime)
{
	std::chrono::duration<float> fs = endTime - startTime;
	auto d = std::chrono::duration_cast<std::chrono::milliseconds>(fs);
	std::cout << "Total execution time: " << fs.count() << " s" << std::endl;
}

//void Game::render()
//{
//	world->renderWorld();
//}