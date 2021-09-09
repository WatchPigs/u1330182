#include "Player.h"
#include <iostream>
#include <iomanip>
using namespace std;

Player::Player(int x, int y) : GameObject(x, y)
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