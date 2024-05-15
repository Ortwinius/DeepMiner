#pragma once

#include "robot.h"
#include <algorithm>

/*
EarthCrusher sorts the column of blocks descendingly and mines the first block (most valuable) in the column.
*/
class EarthCrusher : public Robot
{
public:
	EarthCrusher(const std::string& name) : Robot(name) {}
	~EarthCrusher() = default;

	void mine(std::vector<Block>& robotColumn) override;
};