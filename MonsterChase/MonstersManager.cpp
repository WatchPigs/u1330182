#include "MonstersManager.h"
#include "GlobalSettings.h"
#include <iostream>
#include <iomanip>
using namespace std;

MonstersManager::MonstersManager()
{
	m_entry = NULL;
	m_tail = NULL;
	srand((unsigned int)time(NULL));
}

MonstersManager::~MonstersManager()
{
	if (m_entry)
	{
		MonsterNode* it = m_entry;
		while (it)
		{
			MonsterNode* temp = it;
			it = temp->next;
			delete temp->self;
			delete temp;
		}
	}
}

void MonstersManager::Add(Monster* m)
{
	if (m_entry)
	{
		MonsterNode* newNode = new MonsterNode;
		newNode->self = m;
		newNode->last = m_tail;
		newNode->next = NULL;
		m_tail->next = newNode;
		m_tail = newNode;
	}
	else
	{
		MonsterNode* newNode = new MonsterNode;
		newNode->self = m;
		newNode->last = NULL;
		newNode->next = NULL;
		m_entry = newNode;
		m_tail = newNode;
	}
}

MonsterNode* MonstersManager::Find(char* name)
{
	if (m_entry == NULL) return NULL;
	MonsterNode* it = m_entry;
	while (it != NULL)
	{
		if (it->self->GetName() == name)
		{
			return it;
		}
	}
	return NULL;
}

void MonstersManager::Remove(MonsterNode* mn)
{
	if (mn == m_entry || mn == m_tail)
	{
		if (mn == m_tail) m_tail = m_tail->last;
		if (mn == m_entry) m_entry = m_entry->next;
	}
	else if (mn->last != NULL && mn->next != NULL)
	{
		mn->last->next = mn->next;
		mn->next->last = mn->last;
	}
	delete mn->self;
	delete mn;
}

int MonstersManager::SamePositionAmount()
{
	int amount = 0;
	MonsterNode* it1 = m_entry;
	if (!it1) return amount;
	while (it1->next)
	{
		MonsterNode* it2 = it1->next;
		while (it2)
		{
			if (it2->self->GetPoint() == it1->self->GetPoint()) amount++;
			it2 = it2->next;
		}
		it1 = it1->next;
	}
	return amount;
}

void MonstersManager::MonstersAct()
{
	MonsterNode* it = m_entry;
	while (it)
	{
		MonsterNode* temp = it;
		if (it->self->GetLifetime() == 0)
		{
			it = it->next;
			cout << temp->self->GetName() << " ran out of its lifetime and dead" << endl;
			Remove(temp);
		}
		else
		{
			it->self->Act();
			it = it->next;
		}
	}
	int samePosAmt = SamePositionAmount();
	for (int i = 0; i < samePosAmt; i++)
	{
		int x = rand() % RANGE;
		int y = rand() % RANGE;
		char name[] = "NEWBIE";
		Monster* m = new Monster(name, x, y, LIFETIME);
		Add(m);
	}
}

bool MonstersManager::Encountered(Point2D p)
{
	if (m_entry)
	{
		MonsterNode* it = m_entry;
		while (it)
		{
			if (it->self->GetPoint() == p) return true;
			it = it->next;
		}
	}
	return false;
}

void MonstersManager::Print()
{
	cout << "Monsters:" << endl;
	MonsterNode* it = m_entry;
	while (it)
	{
		cout << it->self->GetName() << " is at [" << setw(4) << it->self->GetPoint().GetX() << "," << setw(4) << it->self->GetPoint().GetY() << "]" << endl;
		it = it->next;
	}
}