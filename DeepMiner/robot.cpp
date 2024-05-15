#include "robot.h"

Robot::Robot(const std::string& name)
	: name(name)
	, score(0)
	, alive(true)
	, kills(0)
	, dir(idle)
	, pos(Vec3(0, 0, 0))
{
	initRobot();
}

void Robot::initRobot()
{
	this->pos = Vec3(rand() % WorldDimensions::dimX, rand() % WorldDimensions::dimY, DefaultValues::startingHeight);
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

//attack other miner (on same field/next field) and kills him with 40% chance
void Robot::attackRobot(Robot& other)
{
	// lockguard for mutual exclusion
	std::lock_guard<std::mutex> lock(other.robotMutex);
	//std::cout << std::endl << name << " attacks " << other.name << std::endl;
	if (rand() % 100 < DefaultValues::RobotKillProb)
	{
		other.alive = false;
		this->kills++;
		//std::cout << "Robot killed!" << std::endl;
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

// for final score output
void Robot::getRobotStats()
{
	std::cout << std::endl;
	std::cout << "Robot: " << name << std::endl;
	std::cout << "Score: " << score << std::endl;
	std::cout << "Alive: " << (alive ? "true" : "false") << std::endl;
	std::cout << "Kills: " << kills << std::endl;
	std::cout << "Thread execution time: " << robotThreadExecutionTime << " ms" << std::endl;
	std::cout << std::endl;
}
