#include "Vector2.h"

namespace Engine
{
	Vector2::Vector2(float x, float y)
	{
		m_x = x;
		m_y = y;
	}

	float Vector2::GetX() const
	{
		return m_x;
	}

	float Vector2::GetY() const
	{
		return m_y;
	}

	void Vector2::SetX(float x)
	{
		m_x = x;
	}

	void Vector2::SetY(float y)
	{
		m_y = y;
	}

	void Vector2::operator+=(const Vector2& other)
	{
		m_x += other.GetX();
		m_y += other.GetY();
	}

	void Vector2::operator-=(const Vector2& other)
	{
		m_x -= other.GetX();
		m_y -= other.GetY();
	}

	void Vector2::operator*=(float i)
	{
		m_x *= i;
		m_y *= i;
	}

	void Vector2::operator/=(float i)
	{
		m_x /= i;
		m_y /= i;
	}

	Vector2 Vector2::operator*(float i) const
	{
		return Vector2(m_x * i, m_y * i);
	}

	Vector2 Vector2::operator/(float i) const
	{
		return Vector2(m_x / i, m_y / i);
	}

	Vector2 Vector2::operator+(Vector2 p) const
	{
		return Vector2(m_x + p.GetX(), m_y + p.GetY());
	}

	Vector2 Vector2::operator-(Vector2 p) const
	{
		return Vector2(m_x - p.GetX(), m_y - p.GetY());
	}

	bool Vector2::operator==(Vector2 p) const
	{
		if (m_x == p.GetX() && m_y == p.GetY()) return true;
		else return false;
	}

	bool Vector2::operator!=(Vector2 p) const
	{
		if (m_x == p.GetX() && m_y == p.GetY()) return false;
		else return true;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-m_x, -m_y);
	}

	Vector2 operator*(float i, Vector2 p)
	{
		return Vector2(p.GetX() * i, p.GetY() * i);
	}

	const Vector2 Vector2::Zero(0.0f, 0.0f);
}
