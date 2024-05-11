#include "block.h"
#include <iostream>

/*
	determine state of block by randomized value 
	between 0 and 1 and the corresponding blocks tate
*/ 

const BlockType& Block::createRandomBlockType(std::mt19937& gen)
{
	BlockType type = BlockType::air;

	double rand = static_cast<double>(generateRandomNumber(gen, 0, 100)) / 100;

	if (rand < BlockTypeProbs::stoneP)
	{
		type = BlockType::stone;
	}
	else if (rand < (BlockTypeProbs::stoneP + BlockTypeProbs::ironP))
	{
		type = BlockType::iron;
	}
	else if (rand < (BlockTypeProbs::stoneP + BlockTypeProbs::ironP + BlockTypeProbs::goldP))
	{
		type = BlockType::gold;
	}
	else
	{
		type = BlockType::vibranium;
	}

	std::cout << "Created block of type " << type << std::endl;
	return type;
}
