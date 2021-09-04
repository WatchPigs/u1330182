#include "Point2D.h"

Point2D::Point2D(int x, int y)
{
	m_x = x;
	m_y = y;
}

int Point2D::GetX() const
{
	return m_x;
}

int Point2D::GetY() const
{
	return m_y;
}

void Point2D::SetX(int x)
{
	m_x = x;
}

void Point2D::SetY(int y)
{
	m_y = y;
}

void Point2D::operator+=(Point2D& other)
{
	m_x += other.GetX();
	m_y += other.GetY();
}

Point2D Point2D::operator*(int i) const
{
	return Point2D(m_x * i, m_y * i);
}

Point2D Point2D::operator+(Point2D p) const
{
	return Point2D(m_x + p.GetX(), m_y + p.GetY());
}

Point2D Point2D::operator-(Point2D p) const
{
	return Point2D(m_x - p.GetX(), m_y - p.GetY());
}

bool Point2D::operator==(Point2D p) const
{
	if (m_x == p.GetX() && m_y == p.GetY()) return true;
	else return false;
}