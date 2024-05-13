#include "earthcrusher.h"

/*
EarthCrusher sorts column in descending order and mines the highest block.
He purifies the mined element with a mulitplier of 1.5
*/

void EarthCrusher::mine(std::vector<Block>& robotColumn)
{ 
	// sort blocks in descending order
	std::sort(robotColumn.begin(), robotColumn.begin() + this->pos.z);

	// if highest value is air return (nothing to mine)
	if (robotColumn[this->pos.z].getBlockType() == BlockType::air)
	{
		return;
	}

	// get highest block score (= where player currently stands)
	this->score += convertBlockTypeToScoreValue(robotColumn[this->pos.z].getBlockType());

	// set that value to air
	robotColumn[this->pos.z].setBlockType(BlockType::air);

	// update robot height
	updateRobotHeight(robotColumn);
}
