#include "voidifier.h"

/*
Voidifier xray-mines the most-valuable block, the column collapses under him (= moves down by one block).
*/
void Voidifier::mine(std::vector<Block>& robotColumn)
{
    int highestValue = -1; // Initialize with a low value
    int highestValueIndex = -1; // Initialize with an invalid index

    for (int i = 0; i < robotColumn.size(); ++i)
    {
        if (robotColumn[i].getBlockType() > highestValue)
        {
            highestValue = robotColumn[i].getBlockType();
            highestValueIndex = i;
        }
    }

    // If no blocks are present or all are air, return
    if (highestValueIndex == -1)
        return;

    // Add the value of the highest block the player stands on and the highest value block to the score
    this->score += convertBlockTypeToScoreValue(static_cast<BlockType>(highestValue));
    robotColumn[highestValueIndex].setBlockType(BlockType::air);

    // if mined value is block player stands on -> return
    if (this->pos.z == highestValueIndex)
        return;

    // Move rest of the column elements above the mined block one position down
    for (int i = highestValueIndex + 1; i < robotColumn.size(); ++i)
    {
        robotColumn[i - 1] = robotColumn[i];
    }

    // Set the last element to air
    robotColumn[robotColumn.size() - 1].setBlockType(BlockType::air);

    // update robot height
    updateRobotHeight(robotColumn);
}
