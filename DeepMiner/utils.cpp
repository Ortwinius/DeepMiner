#include "utils.h"

int generateRandomNumber(std::mt19937& gen, int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(gen);
}

int convertBlockTypeToScoreValue(const BlockType& blockType)
{
	switch (blockType)
	{
	case air:
		return 0;
	case stone:
		return BlockTypeScoreValue::stoneV;
	case iron:
		return BlockTypeScoreValue::ironV;
	case gold:
		return BlockTypeScoreValue::goldV;
	case vibranium:
		return BlockTypeScoreValue::vibraniumV;
	default:
		return 0;
	}

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

const std::string convertBlockTypeToString(const BlockType& blockType)
{
	switch (blockType)
	{
	case air:
		return "Air";
	case stone:
		return "Stone";
	case iron:
		return "Iron";
	case gold:
		return "Gold";
	case vibranium:
		return "Vibranium";
	default:
		return "Air";
	}
}



