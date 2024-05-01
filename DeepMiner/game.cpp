#include "game.h"

Game::Game()
{
	initGame();
}

Game::~Game()
{
	if (world != nullptr)
	{
		delete world;
	}
}

void Game::initGame()
{
	running = true;
	world = new World();
}

void Game::handleInput()
{
	// show movement options
	std::cout << "[W] - Forward" << std::endl;
	std::cout << "[A] - Backward" << std::endl;
	std::cout << "[S] - Down" << std::endl;
	std::cout << "[D] - Right" << std::endl;
	std::cout << "[I] - Idle" << std::endl;

	char input;
	bool inputValidated = false;

	while (!inputValidated)
	{
		std::cin >> input;

		switch (input)
		{
		case 'W':
		case 'w':
			playerMovementDir = Direction::forward;
			inputValidated = true;
			break;
		case 'A':
		case 'a':
			playerMovementDir = Direction::left;
			inputValidated = true;
			break;
		case 'S':
		case 's':
			playerMovementDir = Direction::backward;
			inputValidated = true;
			break;
		case 'D':
		case 'd':
			playerMovementDir = Direction::right;
			inputValidated = true;
			break;
		case 'I':
		case 'i':
			playerMovementDir = Direction::idle;
			inputValidated = true;
			break;
		default:
			std::cout << "Error: Input not valid" << std::endl;
			break;
		}
	}
}


void Game::update()
{
	world->updateWorld(playerMovementDir);
}

void Game::render()
{
	world->renderWorld();
}
