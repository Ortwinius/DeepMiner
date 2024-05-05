#include "robot.h"

void Robot::move(const Direction& toMove)
{
	Vec3 delta = getDirectionVec(toMove);
	Vec3 newPos = this->pos + delta;
	if (isValidPosition(newPos))
	{
		std::cout << "Moving from (" << pos.x << "," << pos.y << "," << pos.z << ") to:" << std::endl;
		this->pos += getDirectionVec(toMove);
		std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}
	else
	{
		std::cout << "Can't move here! Staying idle" << std::endl;
	}
}

Vec3 Robot::getDirectionVec(const Direction& toMove)
{
	switch (toMove)
	{
	case Direction::idle:
		return Vec3(0, 0, 0);
	case forward:
		return Vec3(0, -1, 0);
	case backward:
		return Vec3(0, 1, 0);
	case left:
		return Vec3(-1, 0, 0);
	case right:
		return Vec3(1, 0, 0);
	case up:
		return Vec3(0, 0, 1);
	case down:
		return Vec3(0, 0, -1);
	}

	return Vec3(0, 0, 0);

}

const bool Robot::isValidPosition(const Vec3& pos)
{
	return (pos.x >= 0 && pos.x < WorldDimensions::dimX
		&& pos.y >= 0 && pos.y < WorldDimensions::dimY
		&& pos.z >= 0 && pos.z < WorldDimensions::dimZ);
}


