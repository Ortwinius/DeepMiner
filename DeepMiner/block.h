#pragma once
#include "common.h"

class Block
{
public:
	Block()
		: blockType(BlockType::air)
	{}

	Block(std::mt19937& gen)
	{
		blockType = createRandomBlockType(gen);
	}

	Block(const Block& other)
		: blockType(other.blockType)
	{}

	const BlockType& getBlockType() { return blockType; }
	void setBlockType(const BlockType& type) { blockType = type; }

private:

	const BlockType& createRandomBlockType(std::mt19937& gen);

	BlockType blockType;
};