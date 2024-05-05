#pragma once

#include "robot.h"

/*Der Roboter nimmt sich den Wert seiner
Koordinaten sowie der naechsten zwei z - Werte.*/

class StarSweeper : public Robot
{
public:
	StarSweeper(bool isAI) : Robot(isAI) {}
	~StarSweeper() = default;

	//void move(const Direction& toMove) override
	//{

	//}

	void mine() override
	{
		std::cout << std::endl << "Starsweeper mines blocks" << std::endl;
		// world grid -> column take highest value and two below. 
		// read the values and add them depending on rareness

	}
};