#include "robot.h"

void Robot::move(RandGen& gen)
{
	Direction toMove = static_cast<Direction>(generateRandomNumber(gen, 0, 4));
	Vec3 delta = getDirectionVec(toMove);
	Vec3 newPos = this->pos + delta;

	if (isValidPosition(newPos))
	{
		//std::cout << "Moving from (" << pos.x << "," << pos.y << "," << pos.z << ") to:" << std::endl;
		this->pos = newPos;
		//std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}
	else
	{
		//std::cout << "Can't move here! Staying idle" << std::endl;
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

// TODO: also check if there is no robot on the field?
const bool Robot::isValidPosition(const Vec3& pos)
{
	return (pos.x >= 0 && pos.x < WorldDimensions::dimX
		&& pos.y >= 0 && pos.y < WorldDimensions::dimY
		&& pos.z >= 0 && pos.z < WorldDimensions::dimZ);
}

void Robot::updateRobotHeight(std::vector<Block>& robotColumn)
{
	int newHeight = 0;

	for (int z = WorldDimensions::dimZ - 1; z >= 0; z--)
	{
		if (robotColumn[z].getBlockType() != BlockType::air)
		{
			newHeight = z;
			break;
		}
	}

	this->pos.z = newHeight;
}

