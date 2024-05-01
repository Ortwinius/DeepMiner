#include "utils.h"

int generateRandomNumber(std::mt19937& gen, int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(gen);
}

const char convertBlockToChar(const BlockType& blockType)
{
	switch (blockType)
	{
	case air:
		return ' ';
	case stone:
		return '#';
	case iron:
		return 'I';
	case gold:
		return 'G';
	case vibranium:
		return 'V';
	default:
		return ' ';
	}
}

