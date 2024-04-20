#pragma once
#include "world.h"

class Game
{
public:
	Game();
	~Game();
	void handleInput();
	void update();
	void render();
	const bool isRunning() { return running; }
private:
	void initGame();
	bool running = false;
	World* world;
	Direction movementDirection;
};