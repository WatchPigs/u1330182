#include "Player.h"
#include "GlobalSettings.h"
#include <iostream>
#include <iomanip>
using namespace std;

Player::Player(int x, int y) : GameObject(x, y, 0, RANGE, 0, RANGE)
{

}

void Player::Move(int x, int y)
{
	__move(x, y);
}

void Player::Print()
{
	cout << "Player:" << endl;
	cout << "You are at [" << setw(4) << m_point.GetX() << setw(4) << m_point.GetY() << "]" << endl;
}