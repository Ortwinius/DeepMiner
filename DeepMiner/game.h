#pragma once
#include "world.h"

class Game
{
public:
	Game();
	~Game();
	void handleInput();
	void update();
	void renderUI();
	const bool isRunning() { return running; }
private:
	void init();
	bool running = false;
	World* world;
};