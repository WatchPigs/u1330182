#pragma once
#include "Point2D.h"

namespace Engine
{
	class GameObject
	{
	protected:
		Point2D m_point;
		int m_RangeMinX;
		int m_RangeMinY;
		int m_RangeMaxX;
		int m_RangeMaxY;
		void __move(int x, int y);
		int __clamp(int min, int max, int num);
	public:
		GameObject(int x, int y, int minX, int maxX, int minY, int maxY);
		Point2D GetPoint();
	};

}

