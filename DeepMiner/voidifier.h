#pragma once

#include "robot.h"

class Voidifier : public Robot
{
public:
	Voidifier(bool isAI) : Robot(isAI) {}
	~Voidifier() = default;

	void mine(std::vector<Block>& robotColumn) override
	{
		std::cout << std::endl << "Voidifier mines blocks" << std::endl;
		// TODO
	}

};