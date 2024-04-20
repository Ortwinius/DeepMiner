#include "robot.h"

Vec3 Robot::getDirectionVec(const Direction& toMove)
{
	switch (toMove)
	{
	case idle:
		return Vec3(0, 0, 0);
	case forward:
		return Vec3(-1, 0, 0);
	case backward:
		return Vec3(1, 0, 0);
	case left:
		return Vec3(0, -1, 0);
	case right:
		return Vec3(0, 1, 0);
	case up:
		return Vec3(0, 0, 1);
	case down:
		return Vec3(0, 0, -1);
	}

	return Vec3(0, 0, 0);

}
