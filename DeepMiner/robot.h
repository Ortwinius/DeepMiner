#pragma once

#include <iostream>
#include <random>
#include <mutex>
#include "common.h"

/*
Robot interface class with pure virtual function mine() => to be implemented by derived classes.
*/
class Robot
{
public:
	typedef std::mt19937 RandGen;
	typedef std::vector<std::vector<std::vector<Block>>> WorldGrid;

	explicit Robot(const std::string& name);                 
	virtual ~Robot() = default;

	void move(WorldGrid& world, RandGen& gen);
	void attackRobot(Robot& other);

	virtual void mine(std::vector<Block>& robotColumn) = 0;
	
	const int getScore() const { return score; }
	const Direction& getDirection() const { return dir; }
	const Vec3& getPos() const { return pos; }
	const bool isAlive() const { return alive; }
	const std::string& getName() const { return name; }
	const double& getThreadExecutionTime() const { return robotThreadExecutionTime; }
	void setThreadExecutionTime(double time) { robotThreadExecutionTime = time; }
	const bool isValidPosition(const Vec3& pos);
	void updateRobotHeight(std::vector<Block>& robotColumn);
	Vec3 getDirectionVec(const Direction& toMove);
	void getRobotStats();

protected:
	int score;
	int kills;
	Direction dir;
	Vec3 pos;
	bool alive;
	std::string name;
	std::mutex robotMutex; //mutex for robot attacks
	double robotThreadExecutionTime; //thread execution time saved inside
	void initRobot();
};