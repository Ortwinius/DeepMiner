#pragma once

#include "robot.h"
#include <algorithm>

class EarthCrusher : public Robot
{
public:
	EarthCrusher() : Robot() {}
	~EarthCrusher() = default;

	void mine(std::vector<Block>& robotColumn) override;
};