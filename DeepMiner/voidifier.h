#pragma once

#include "robot.h"

class Voidifier : public Robot
{
public:
	Voidifier() : Robot() {}
	~Voidifier() = default;

	void mine(std::vector<Block>& robotColumn) override;

};