#pragma once

class Vec3
{
public:
	Vec3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vec3(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// Pos1 += Pos2;
	void operator += (const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}
	// Pos1 + Pos2
	const Vec3 operator + (const Vec3& other) const
	{
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	// -(Pos1) = -pos.x, -pos.y
	const Vec3 operator - () const
	{
		return Vec3(-x, -y, -z);
	}
	// Pos3 = Pos2 - Pos1
	const Vec3 operator - (const Vec3& other) const
	{
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	const bool operator == (const Vec3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	const bool operator != (const Vec3& other) const
	{
		return x != other.x && y != other.y && z != other.z;
	}

	int x;
	int y;
	int z;
};