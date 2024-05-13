#include "starsweeper.h"

// world grid -> column take highest value (z value of robot) and two below. 
// read the values and add them depending on rareness

void StarSweeper::mine(std::vector<Block>& robotColumn)
{

	for (int z = this->pos.z, i = 0; z >= 0 && i < 3; z--, i++)
	{
		this->score += convertBlockTypeToScoreValue(robotColumn[z].getBlockType());
		robotColumn[z].setBlockType(BlockType::air);
	}
	updateRobotHeight(robotColumn);
}
