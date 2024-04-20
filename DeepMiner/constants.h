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

namespace WorldDimensions
{
	constexpr int dimX = 5;
	constexpr int dimY = 5;
	constexpr int dimZ = 10;
}