#pragma once

#include "robot.h"

/*Der Roboter nimmt sich den Wert seiner
Koordinaten sowie der naechsten zwei z - Werte.*/

class StarSweeper : public Robot
{
public:
	StarSweeper(bool isAI) : Robot(isAI) {}
	~StarSweeper() = default;

	void mine(std::vector<Block>& robotColumn) override
	{	
		// world grid -> column take highest value (z value of robot) and two below. 
		// read the values and add them depending on rareness

		std::cout << std::endl << "Starsweeper mines blocks" << std::endl;

		for (int z = this->pos.z, i = 0; z >= 0 && i < 3; z--, i++)
		{
			this->score += convertBlockTypeToScoreValue(robotColumn[z].getBlockType());
			robotColumn[z].setBlockType(BlockType::air);
		}
	}
};