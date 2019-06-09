#include "Vector2D.h"
#include <SDL_assert.h>

Vector2D Vector2D::ApplyRotation( float32 rotation)
{
	Vector2D v;
	float32 rad = rotation * M_PI / 180;
	v.x = v.x * cos(rad) - v.y * sin(rad);
	v.y = v.x * sin(rad) + v.y * cos(rad);
	return v;
}
Vector2D Vector2D::Divide( float f)
{
	x = x / f;
	y = y / f;
	return *this;
}
Vector2D Vector2D::Multiply(float f)
{
	x = x * f;
	y = y * f;
	return *this;
}
float Vector2D::AreEqual( Vector2D vy)
{
	float xy = x * vy.x + y * vy.y;
	float modxy = Length() * vy.Length();
	return acos(xy / modxy);
}
//Degrees

Vector2D Vector2D::operator/(float32 d) const
{
	Vector2D v;
	v.x = v.x / d;
	v.y = v.y / d;
	return v;
}

Vector2D Vector2D::operator*(float32 d) const
{
	Vector2D v;
	v.x = v.x * d;
	v.y = v.y * d;
	return v;
}

Vector2D Vector2D::operator+(float32 d) const
{
	Vector2D v;
	v.x = v.x + d;
	v.y = v.y + d;
	return v;
}

Vector2D Vector2D::operator-(float32 d) const
{
	Vector2D v;
	v.x = v.x - d;
	v.y = v.y - d;
	return v;
}

double Vector2D::Angle() const {
	return atan(y/x);
}

double Vector2D::Angle(Vector2D b) const {
	double dot = x * b.x + y * b.y;
	double det = x * b.y - y * b.x;
	return atan2(det, dot);
}