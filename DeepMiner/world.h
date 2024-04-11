#pragma once

#include <vector>
#include "starsweeper.h"

class World
{
public:
	World();
	~World();

	void init();
private:
	StarSweeper* player;
	//std::vector<Roboter> entities;

};