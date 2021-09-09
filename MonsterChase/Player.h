#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(int x, int y);
	void Move(int x, int y);
	void Print();
};

