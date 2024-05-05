#pragma once

#include "robot.h"

class Voidifier : public Robot
{
public:
	Voidifier(bool isAI) : Robot(isAI) {}
	~Voidifier() = default;

	//void move(const Direction& toMove) override
	//{
	//	std::cout << "Moving from (" << pos.x << "," << pos.y << "," << pos.z << ") to:";
	//	this->pos += getDirectionVec(toMove);
	//	std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	//}

	void mine() override
	{
		std::cout << std::endl << "Voidifier mines blocks" << std::endl;
		// TODO
	}

};