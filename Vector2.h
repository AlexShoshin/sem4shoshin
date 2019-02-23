#pragma once
#include <iostream>

class Vector2
{
public:
	float x, y;
	
	Vector2();
	Vector2(float a, float b);
	Vector2 operator+(const Vector2 other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2 operator-(const Vector2 other) const;
	Vector2& operator-=(const Vector2& other);
	float operator*(const Vector2& other) const;
	float operator^(const Vector2& other) const;
	Vector2 operator*(float a);
	Vector2 operator/(float a);
	Vector2 norm();
	float len();
	float squareLen();
	Vector2 perpen();
	Vector2 operator-() const;
	Vector2& rotate(float angle);
	Vector2 getRotated(float angle) const;
	
};

std::ostream& operator<<(std::ostream& stream, const Vector2& v);
std::istream& operator>>(std::istream& stream, Vector2& v);
Vector2 operator*(float a, const Vector2& v);

