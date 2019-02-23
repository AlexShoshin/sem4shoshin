#include "Vector2.h"
#include <iostream>
#include <math.h>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float a, float b)
{
	x = a;
	y = b;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& v)
{
	stream << "(" << v.x << ", " << v.y << ")";
	return stream;
}

std::istream& operator>>(std::istream& stream, Vector2& v)
{
	stream >> v.x >> v.y;
	return stream;
}

Vector2 Vector2::operator+(const Vector2 other) const
{
	Vector2 result;
	result.x = x + other.x;
	result.y = y + other.y;
	return result;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2 other) const
{
	Vector2 result;
	result.x = x - other.x;
	result.y = y - other.y;
	return result;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

float Vector2::operator*(const Vector2& other) const
{
	int result = x * other.x + y * other.y;
	return result;
}

float Vector2::operator^(const Vector2& other) const
{
	int result = x * other.y - y * other.x;
	return result;
}

Vector2 Vector2::operator*(float a)
{
	return Vector2(x * a, y * a);
}

Vector2 operator*(float a, const Vector2& v)
{
	return Vector2(v.x * a, v.y * a);
}

Vector2 Vector2::operator/(float a)
{
	return Vector2(x / a, y / a);
}

float Vector2::len()
{
	return sqrt(x * x + y * y);
}

float Vector2::squareLen()
{
	return x * x + y * y;
}

Vector2 Vector2::norm()
{
	return Vector2(x / len(), y / len());
}

Vector2 Vector2::perpen()
{
	return Vector2(y, -x);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2& Vector2::rotate(float angle)
{
	int x0 = x;
	int y0 = y;
	x = x0 * cos(angle) - y0 * sin(angle);
	y = x0 * sin(angle) + y0 * cos(angle);
	return *this;
}

Vector2 Vector2::getRotated(float angle) const
{
	Vector2 result;
	int x0 = x;
	int y0 = y;
	result.x = x0 * cos(angle) - y0 * sin(angle);
	result.y = x0 * sin(angle) + y0 * cos(angle);
	return result;
}

