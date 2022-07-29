#include "Player.h"
#include "Player.h"
#include "GlobalSettings.h"
#include <iostream>
#include <iomanip>
using namespace std;

Player::Player(char name[], int x, int y) : Engine::GameObject(x, y, 0, RANGE, 0, RANGE)
{
	m_name = new char[strlen(name) + 1];
	for (int i = 0; i <= (int)strlen(name); i++)
	{
		m_name[i] = name[i];
	}
}

Player::~Player()
{
	delete[] m_name;
}

void Player::Move(int x, int y)
{
	Engine::GameObject::__move(x, y);
}

void Player::Print()
{
	cout << "Player:" << endl;
	cout << "You(" << m_name << ") are at [" << setw(4) << Engine::GameObject::m_point.GetX() << "," << setw(4) << Engine::GameObject::m_point.GetY() << "]" << endl;
}