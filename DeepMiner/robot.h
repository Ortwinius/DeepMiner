#pragma once

#include <iostream>
#include <random>
#include "common.h"

class Robot
{
public:
	Robot()
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
		// TODO: replace with random(?) starting position
		// check for collision with other robot?
		pos = Vec3(rand() % 10, rand() % 10, DefaultValues::startingHeight);
		std::cout << "Initialized bot at pos (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}

	virtual void move(const Direction& toMove) = 0;

	virtual void mine() = 0;
	
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