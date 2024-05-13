#include "robot.h"

Robot::Robot()
{
	score = 0;
	dir = idle;
	pos = Vec3(0, 0, 0);
	alive = true;
	initRobot();
}

void Robot::initRobot()
{
	pos = Vec3(rand() % WorldDimensions::dimX, rand() % WorldDimensions::dimY, DefaultValues::startingHeight);
}

void Robot::move(WorldGrid& world, RandGen& gen)
{
	// generate random direction
	Direction toMove = static_cast<Direction>(generateRandomNumber(gen, 0, 4));
	Vec3 delta = getDirectionVec(toMove);
	Vec3 newPos = this->pos + delta;

	if (isValidPosition(newPos))
	{
		this->pos = newPos;
	}

	updateRobotHeight(world[pos.x][pos.y]);
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

