#pragma once

#include "robot.h"

class StarSweeper : public Robot
{
public:
	StarSweeper() {}
	~StarSweeper() {}

	/*Der Roboter nimmt sich den Wert seiner 
	Koordinaten sowie der n¨achsten zwei z - Werte.*/ 

	void move(const Direction& toMove)
	{
		std::cout << "Moving from (" << pos.x << "," << pos.y << "," << pos.z << ") to:" << std::endl;
		this->pos += getDirectionVec(toMove);
		std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}

	void mine()
	{
		std::cout << std::endl << "Starsweeper mines blocks" << std::endl;
	}
};