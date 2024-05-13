#pragma once

#include <iostream>
#include <random>
#include "common.h"

typedef std::mt19937 RandGen;

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
		pos = Vec3(rand() % WorldDimensions::dimX, rand() % WorldDimensions::dimY, DefaultValues::startingHeight);
		//std::cout << "Initialized bot at pos (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}

	virtual void move(RandGen& gen);

	virtual void mine(std::vector<Block>& robotColumn) = 0;
	
	const bool isValidPosition(const Vec3& pos);
	void updateRobotHeight(std::vector<Block>& robotColumn);
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