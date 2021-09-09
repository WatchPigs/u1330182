#pragma once
#include "Point2D.h"

class GameObject
{
protected:
	Point2D m_point;
	void __move(int x, int y);
	int __clamp(int min, int max, int num);
public:
	GameObject(int x, int y);
	Point2D GetPoint();
};


