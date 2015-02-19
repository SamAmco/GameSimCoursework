#pragma once
#include <iostream>
#include <cmath>

class PhysVector3
{
public:

	PhysVector3(const float x, const float y, const float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline float getX() const { return x; }
	inline float getY() const { return y; }
	inline float getZ() const { return z; }

	void setX(float x)
	{
		this->x = x;
		changed = true;
	}
	void setY(float y)
	{
		this->y = y;
		changed = true;
	}
	void setZ(float z)
	{
		this->z = z;
		changed = true;
	}

	PhysVector3 normalise()
	{
		float length = getMagnitude();

		if (length != 0.0f)	
		{
			length = 1.0f / length;
			return PhysVector3(x * length, y * length, z * length);
		}
		std::cout << "Tried to normalise a zero size vector" << std::endl;
		return PhysVector3(0, 0, 0);
	}

	static PhysVector3 zero()
	{
		return PhysVector3(0, 0, 0);
	}

	float getMagnitude()
	{
		if (!changed)
			return magnitude;
		else
		{
			magnitude = sqrt((x*x) + (y*y) + (z*z));
			return magnitude;
		}
	}

	void Invert() 
	{
		x = -x;
		y = -y;
		z = -z;
	}

	PhysVector3 Inverse() const
	{
		return PhysVector3(-x, -y, -z);
	}

	static float dot(const PhysVector3& a, const PhysVector3& b)
	{
		return (a.x*b.x) 
			 + (a.y*b.y) 
			 + (a.z*b.z);
	}

	static PhysVector3 cross(const PhysVector3& a, const PhysVector3& b)
	{
		return PhysVector3(
			(a.y*b.z) - (a.z*b.y),
			(a.z*b.x) - (a.x*b.z),
			(a.x*b.y) - (a.y*b.x));
	}

	~PhysVector3(){}

	inline friend std::ostream& operator<<(std::ostream& o, const PhysVector3& v)
	{
		return (o << "Vector3(" << v.x << "," << v.y << "," << v.z << ")" << std::endl);
	}

	inline PhysVector3 operator+(const PhysVector3& a) const
	{
		return PhysVector3(x + a.x, y + a.y, z + a.z);
	}

	inline PhysVector3 operator-(const PhysVector3& a) const
	{
		return PhysVector3(x - a.x, y - a.y, z - a.z);
	}

	inline PhysVector3 operator-() const
	{
		return PhysVector3(-x, -y, -z);
	}

	inline void operator+=(const PhysVector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}

	inline void operator-=(const PhysVector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	inline PhysVector3 operator*(const float a) const
	{
		return PhysVector3(x * a, y * a, z * a);
	}

	inline PhysVector3 operator*(const PhysVector3& a) const
	{
		return PhysVector3(x * a.x, y * a.y, z * a.z);
	}

	inline PhysVector3 operator/(const PhysVector3& a) const
	{
		return PhysVector3(x / a.x, y / a.y, z / a.z);
	}

	inline PhysVector3 operator/(const float v) const
	{
		return PhysVector3(x / v, y / v, z / v);
	}

	inline bool	operator==(const PhysVector3& a) const
	{ 
		return (a.x == x && a.y == y && a.z == z) ? true : false;
	}

	inline bool	operator!=(const PhysVector3& a) const
	{
		return (a.x == x && a.y == y && a.z == z) ? false : true;
	}

private:
	float x;
	float y;
	float z;
	float magnitude;
	bool changed = true;
};

