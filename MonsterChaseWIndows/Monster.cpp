#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "Monster.h"
#include "GlobalSettings.h"
#include <iostream>
using namespace std;

Monster::Monster(char name[], int x, int y, int lifetime) : GameObject(x, y, 0, RANGE, 0, RANGE)
{
	m_name = new char[strlen(name) + 1];
	for (int i = 0; i <= (int)strlen(name); i++)
	{
		m_name[i] = name[i];
	}
	srand((unsigned int)time(NULL));
	m_lifetime = lifetime;
}

Monster::~Monster()
{
	delete[] m_name;
}

char* Monster::GetName() const
{
	return m_name;
}

void Monster::Act()
{
	m_lifetime--;
	int direction = rand() % 4;
	switch (direction)
	{
	case 0:
		__move(1, 0);
		break;
	case 1:
		__move(0, 1);
		break;
	case 2:
		__move(-1, 0);
		break;
	default:
		__move(0, -1);
	}
}

int Monster::GetLifetime() const
{
	return m_lifetime;
}