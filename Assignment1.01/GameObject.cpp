#include "GameObject.h"
#include "GlobalSettings.h"


GameObject::GameObject(int x, int y) : m_point(x, y)
{
}


void GameObject::__move(int x, int y)
{
	m_point.SetX(__clamp(0, RANGE, x + m_point.GetX()));
	m_point.SetY(__clamp(0, RANGE, y + m_point.GetY()));
}

Point2D GameObject::GetPoint()
{
	return m_point;
}

int GameObject::__clamp(int min, int max, int num)
{
	if (num < min) return min;
	if (num > max) return max;
	return num;
}