#pragma once
#include <math.h>
#include <random>
#define PI 3.141592f

struct Vector2
{
	static Vector2 Up;
	static Vector2 Right;
	static Vector2 One;
	static Vector2 Zero;
	static Vector2 Center;

	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}

	Vector2(int x, int y)
		: x((float)x)
		, y((float)y)
	{

	}

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}

	Vector2 operator+(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x + other.x;
		temp.y = y + other.y;
		return temp;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;
		return temp;
	}

	Vector2 operator*(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}

	Vector2 operator*(const float ratio)
	{
		Vector2 temp;
		temp.x = x * ratio;
		temp.y = y * ratio;

		return temp;
	}

	Vector2 operator/(const float ratio)
	{
		Vector2 temp;
		temp.x = x / ratio;
		temp.y = y / ratio;

		return temp;
	}

	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator-=(const float& value)
	{
		x -= value;
		y -= value;
	}

	void operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
	}

	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}

	bool operator==(const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}

	void Clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float length = Length();

		if (Length() == 0.0f)
			return *this;

		x /= length;
		y /= length;

		return *this;
	}
};

namespace kw::math
{
	//float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
	//float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);

	inline static Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.0f) * PI;
		vector.Normalize();

		float x = vector.x * cosf(radian) - vector.y * sinf(radian);
		float y = vector.x * sinf(radian) + vector.y * cosf(radian);
		//atan
		//atan();
		return Vector2(x, y);
	}

	inline static float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline static float Cross(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}
	
	static Vector2 Direction(Vector2 start, Vector2 end)
	{
		Vector2 vec = end - start;
		vec.Normalize();

		return vec;
	}

	static int GetRandomNumber(int start, int end)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(start, end);

		return dis(gen);
	}
}