#pragma once
#include "GameObject.h"


class Monster : public GameObject
{
private:
	int m_lifetime;
	char* m_name;
public:
	Monster(char name[], int x, int y, int lifetime);
	~Monster();
	char* GetName() const;
	int GetLifetime() const;
	void Act();
};

