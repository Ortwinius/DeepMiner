#pragma once

enum Direction
{
	idle,
	forward,
	backward,
	left,
	right,
	up,
	down
};

enum BlockType
{
	air,
	stone,
	iron,
	gold,
	vibranium,
};
namespace WorldDimensions
{
	constexpr int dimX = 5;
	constexpr int dimY = 5;
	constexpr int dimZ = 10;
}

namespace DefaultValues
{
	constexpr int startingHeight = 9;
	constexpr int minRobotCount = 1; 
	constexpr int maxRobotCount = 3000;
	constexpr int robotClassCount = 3;
	constexpr int RobotKillProb = 20;
}

namespace BlockTypeProbs
{
	constexpr double stoneP = 0.55;
	constexpr double ironP = 0.25;
	constexpr double goldP = 0.15;
	constexpr double vibraniumP = 0.05;
}

namespace BlockTypeScoreValue
{
	constexpr int stoneV = 1;
	constexpr int ironV = 2;
	constexpr int goldV = 4;
	constexpr int vibraniumV = 8;
}