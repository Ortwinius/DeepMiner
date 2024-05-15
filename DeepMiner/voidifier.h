#pragma once

#include "robot.h"

/* 
Voidifier xray-mines the most-valuable block, the column collapses under him (= moves down by one block).
*/
class Voidifier : public Robot
{
public:
	Voidifier(const std::string& name) : Robot(name) {}
	~Voidifier() = default;

	void mine(std::vector<Block>& robotColumn) override;

};