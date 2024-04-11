#pragma once

#include "robot.h"

class StarSweeper : public Robot
{
public:
	StarSweeper() {}
	~StarSweeper() {}

	/*Der Roboter nimmt sich den Wert seiner 
	Koordinaten sowie der n¨achsten zwei z - Werte.*/ 

	void mine()
	{
		std::cout << std::endl << "Starsweeper mines blocks" << std::endl;
	}
};