#pragma once

#include "robot.h"
#include <algorithm>

/*
EarthCrusher sorts column in descending order and mines the highest block.
He purifies the mined element with a mulitplier of 1.5
*/
class EarthCrusher : public Robot
{
public:
	EarthCrusher(bool isAI) : Robot(isAI) {}
	~EarthCrusher() = default;

	void mine(std::vector<Block>& robotColumn) override
	{
		//std::cout << std::endl << "EarthCrusher mines:" << std::endl;
		
		// sort blocks in descending order
		std::sort(robotColumn.begin(), robotColumn.begin() + this->pos.z);
		
		if(robotColumn[this->pos.z].getBlockType() == BlockType::air)
		{
			//std::cout << "Nothing to mine..." << std::endl;
			return;
		}

		// get highest block score (= where player currently stands)
		this->score += convertBlockTypeToScoreValue(robotColumn[this->pos.z].getBlockType());
		//std::cout << convertBlockTypeToString(robotColumn[this->pos.z].getBlockType()) << " mined..." << std::endl;

		// set that value to air
		robotColumn[this->pos.z].setBlockType(BlockType::air);
	}

};