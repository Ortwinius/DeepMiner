#pragma once

#include <iostream>
#include "utils.h"

class Robot
{
public:
	Robot()
	{
		score = 0;
		dir = idle;
		pos = Vec3(0, 0, 0);

		init();
	}
	virtual ~Robot() = default;

	virtual void init()
	{
		// TODO: replace with random(?) starting position
		// check for collision with other robot?
		pos = Vec3(0, 0, 9);
		std::cout << "Initialized bot at pos (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}

	virtual void move(const Direction& toMove)
	{
		std::cout << "Moving from (" << pos.x << "," << pos.y << "," << pos.z << ") to:" << std::endl;
		this->pos += getDirectionVec(toMove);
		std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}

	Vec3 getDirectionVec(const Direction& toMove)
	{
		switch (toMove)
		{
		case idle:
			return Vec3(0, 0, 0);
		case forward:
			return Vec3(-1, 0, 0);
		case backward:
			return Vec3(1, 0, 0);
		case left:
			return Vec3(0, -1, 0);
		case right:
			return Vec3(0, 1, 0);
		case up:
			return Vec3(0, 0, 1);
		case down:
			return Vec3(0, 0, -1);
		}

		return Vec3(0, 0, 0);
	}


	// abstract function move (for every child class different)
	virtual void mine() = 0;

	const int getScore() const { return score; }
	const Direction& getDirection() const { return dir; }
	const Vec3& getPosition() const { return pos; }
private:
	int score;
	Direction dir;
	Vec3 pos;
};