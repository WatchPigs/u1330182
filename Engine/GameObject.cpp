#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject(int x, int y, int minX, int maxX, int minY, int maxY) : m_point(__clamp(minX, maxX, x), __clamp(minY, maxY, y))
	{
		m_RangeMinX = minX;
		m_RangeMaxX = maxX;
		m_RangeMinY = minY;
		m_RangeMaxY = maxY;
	}


	void GameObject::__move(int x, int y)
	{
		m_point.SetX(__clamp(m_RangeMinX, m_RangeMaxX, x + m_point.GetX()));
		m_point.SetY(__clamp(m_RangeMinY, m_RangeMaxY, y + m_point.GetY()));
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
}
