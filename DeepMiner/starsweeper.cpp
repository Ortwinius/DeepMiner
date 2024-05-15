#include "starsweeper.h"

/*
Starsweeper mines the first three z-values of his column from above.
*/

void StarSweeper::mine(std::vector<Block>& robotColumn)
{

	for (int z = this->pos.z, i = 0; z >= 0 && i < 3; z--, i++)
	{
		this->score += convertBlockTypeToScoreValue(robotColumn[z].getBlockType());
		robotColumn[z].setBlockType(BlockType::air);
	}
	updateRobotHeight(robotColumn);
}
