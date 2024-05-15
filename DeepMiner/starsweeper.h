#pragma once

#include "robot.h"

/*
Starsweeper mines the first three z-values of his column from above.
*/

class StarSweeper : public Robot
{
public:
	StarSweeper(const std::string& name) : Robot(name) {}
	~StarSweeper() = default;

	void mine(std::vector<Block>& robotColumn) override;
};