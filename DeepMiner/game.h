#pragma once
#include <memory>
#include "world.h"
#include "constants.h"
#include "robot.h"

class Game
{
public:
	Game();
	~Game();

	void run();
	void update();
	void render();
private:
	bool isRunning = false;
	std::unique_ptr<World> world;
	Direction playerMovementDir;

	void initGame();
	void showRobotScores(const std::vector<std::unique_ptr<Robot>>& robots);

};