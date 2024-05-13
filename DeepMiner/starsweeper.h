#pragma once

#include "robot.h"

/*Der Roboter nimmt sich den Wert seiner
Koordinaten sowie der naechsten zwei z - Werte.*/

class StarSweeper : public Robot
{
public:
	StarSweeper() : Robot() {}
	~StarSweeper() = default;

	void mine(std::vector<Block>& robotColumn) override;
};