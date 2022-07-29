#pragma once
#include "GameObject.h"

class Player : public Engine::GameObject
{
private:
	char* m_name;
public:
	Player(char name[], int x, int y);
	~Player();
	void Move(int x, int y);
	void Print();
};
