#pragma once

#include <iostream>
#include <random>
#include "common.h"

class Robot
{
public:
	typedef std::mt19937 RandGen;
	typedef std::vector<std::vector<std::vector<Block>>> WorldGrid;

	explicit Robot();                 
	virtual ~Robot() = default;

	virtual void initRobot();
	virtual void move(WorldGrid& world, RandGen& gen);

	virtual void mine(std::vector<Block>& robotColumn) = 0;
	
	const int getScore() const { return score; }
	const Direction& getDirection() const { return dir; }
	const Vec3& getPos() const { return pos; }
	const bool isAlive() const { return alive; }

	const bool isValidPosition(const Vec3& pos);
	void updateRobotHeight(std::vector<Block>& robotColumn);
	Vec3 getDirectionVec(const Direction& toMove);

protected:
	int score;
	Direction dir;
	Vec3 pos;
	bool alive;
};