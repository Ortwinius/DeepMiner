#pragma once

#include "robot.h"
#include <algorithm>

class EarthCrusher : public Robot
{
public:
	EarthCrusher(bool isAI) : Robot(isAI) {}
	~EarthCrusher() = default;

	void mine(std::vector<Block>& robotColumn) override
	{
		std::cout << std::endl << "EarthCrusher mines blocks" << std::endl;
		
		// sort blocks in descending order
		std::sort(robotColumn.begin(), robotColumn.begin() + this->pos.z);
		
		// get highest block score (= where player currently stands)
		this->score += convertBlockTypeToScoreValue(robotColumn[this->pos.z].getBlockType());

		// set that value to air
		robotColumn[this->pos.z].setBlockType(BlockType::air);
	}

};