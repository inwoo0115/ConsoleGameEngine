#pragma once

#include "Core.h"

class ENGINE_API Vector2
{
public:
	Vector2(double x = 0, double y = 0);
	~Vector2() = default;

	// ������ �����ε�.
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);

	Vector2 VectorRotation(double angle);

public:
	// x��ǥ / y��ǥ.
	double x = 0;
	double y = 0;
};
