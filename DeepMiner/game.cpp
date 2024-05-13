#include "game.h"

Game::Game()
{
	initGame();
}

Game::~Game()
{}

void Game::initGame()
{
	isRunning = true;
	world = std::make_unique<World>();
	world->renderWorld(); 	// render first frame
}

void Game::showRobotScores(const std::vector<std::unique_ptr<Robot>>& robots)
{
	int i = 1;
	for(auto &robot : robots)
	{
		std::cout << "Robot " << i << " score: " << robot->getScore() << std::endl;
		i++;
	}
}

void Game::run()
{
	while (isRunning)
	{
		update();
		render();
	}
	// show final score
	showRobotScores(world->getRobots());
}

void Game::update()
{
	world->updateWorld();
	if(world->checkWorldEmpty())
	{
		isRunning = false;
	}

}

void Game::render()
{
	//showRobotScores(world->getRobots());
	world->renderWorld();
}
