#pragma once

#include "robot.h"

class Voidifier : public Robot
{
public:
	Voidifier(bool isAI) : Robot(isAI) {}
	~Voidifier() = default;

	// scans column for highest value block, mines it and sets it to stone
	// then set it to stone and mine the highest block the player is standing on 
	// update score

	void mine(std::vector<Block>& robotColumn) override
	{
		std::cout << std::endl << "Voidifier mines:" << std::endl;

		BlockType highestBlockType = BlockType::air;
		
		// look for highest block value
		for (Block& block : robotColumn)
		{
			if (block.getBlockType() > highestBlockType)
			{
				highestBlockType = block.getBlockType();
			}
		}

		// mine block with highest block value and set it to stone
		for (Block& block : robotColumn)
		{
			if (block.getBlockType() == highestBlockType)
			{
				if (highestBlockType == BlockType::air)
				{
					std::cout << "No blocks to mine..." << std::endl;
					return;
				}
				this->score += convertBlockTypeToScoreValue(block.getBlockType());
				std::cout << convertBlockTypeToString(block.getBlockType()) << " mined..." << std::endl;
				block.setBlockType(BlockType::stone);
				break;
			}
		}


		this->score += convertBlockTypeToScoreValue(robotColumn[this->pos.z].getBlockType());
		std::cout << convertBlockTypeToString(robotColumn[this->pos.z].getBlockType()) << " mined..." << std::endl;
		robotColumn[this->pos.z].setBlockType(BlockType::air);

	}

};