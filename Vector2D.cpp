#include <iostream>
#include "Vector2D.h"


using namespace std;

Vector2D::Vector2D(void)
{
	this->x = 0.0;
	this->y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y)
{
	this->x = in_x;
	this->y = in_y;
}

Vector2D operator*(Vector2D v1, double d)
{
	Vector2D newMultVec;
	newMultVec.x = v1.x * d;
	newMultVec.y = v1.y * d;
	return newMultVec;
}

Vector2D operator/(Vector2D v1, double d)
{
	Vector2D newDivVec;
	newDivVec.x = v1.x / d;
	newDivVec.y = v1.y / d;
	return newDivVec;
}

ostream& operator<<(ostream& out, Vector2D& v1)
{
	out << "<" << v1.x << ", " << v1.y << ">";
	return out;
}