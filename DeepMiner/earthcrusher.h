#pragma once

#include "robot.h"

class EarthCrusher : public Robot
{
public:
	EarthCrusher() = default;
	~EarthCrusher() = default;

	void move(const Direction& toMove) override
	{

	}

	void mine() override
	{
		std::cout << std::endl << "Starsweeper mines blocks" << std::endl;
		// TODO
	}

};