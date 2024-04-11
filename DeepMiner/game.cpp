#include "game.h"

Game::Game()
{
	init();
}

Game::~Game()
{
	if (world != nullptr)
	{
		delete world;
	}
}

void Game::init()
{
	running = true;
	world = new World();
}

void Game::handleInput()
{
}

void Game::update()
{
}

void Game::renderUI()
{
}
