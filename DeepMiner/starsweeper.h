#pragma once

#include "robot.h"

/*Der Roboter nimmt sich den Wert seiner
Koordinaten sowie der naechsten zwei z - Werte.*/

class StarSweeper : public Robot
{
public:
	StarSweeper() {}
	~StarSweeper() {}

	void move(const Direction& toMove) override
	{
		std::cout << "Moving from (" << pos.x << "," << pos.y << "," << pos.z << ") to:" << std::endl;
		this->pos += getDirectionVec(toMove);
		std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}

	void mine() override
	{
		std::cout << std::endl << "Starsweeper mines blocks" << std::endl;
		// TODO
	}
};