#pragma once

#include "robot.h"

class EarthCrusher : public Robot
{
public:
	EarthCrusher(bool isAI) : Robot(isAI) {}
	~EarthCrusher() = default;

	//void move(const Direction& toMove) override
	//{
	//	std::cout << "Moving from (" << pos.x << "," << pos.y << "," << pos.z << ") to:" << std::endl;
	//	this->pos += getDirectionVec(toMove);
	//	std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	//}

	void mine() override
	{
		std::cout << std::endl << "EarthCrusher mines blocks" << std::endl;
		// TODO
	}

};