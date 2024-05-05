#pragma once

#include <iostream>
#include <random>
#include "common.h"

class Robot
{
public:
	Robot(bool isAI)
	{
		score = 0;
		dir = idle;
		pos = Vec3(0, 0, 0);
		ai = false;
		initRobot();
	}
	                             
	virtual ~Robot() = default;

	virtual void initRobot()
	{
		// check for collision with other robot?
		pos = Vec3(rand() % WorldDimensions::dimX, rand() % WorldDimensions::dimY, DefaultValues::startingHeight);
		std::cout << "Initialized bot at pos (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}

	virtual void move(const Direction& toMove);

	virtual void mine() = 0;
	
	const bool isValidPosition(const Vec3& pos);
	Vec3 getDirectionVec(const Direction& toMove);

	const int getScore() const { return score; }
	const Direction& getDirection() const { return dir; }
	const Vec3& getPosition() const { return pos; }
	const bool isAI() const { return ai; }

protected:
	int score;
	Direction dir;
	Vec3 pos;
	bool ai;
};