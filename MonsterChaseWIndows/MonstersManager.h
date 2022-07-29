#pragma once
#include <time.h>
#include <stdlib.h>
#include "MonsterNode.h"
#include "Point2D.h"

class MonstersManager
{
private:
	MonsterNode* m_entry;
	MonsterNode* m_tail;
public:
	MonstersManager();
	~MonstersManager();
	void Add(Monster* m);
	MonsterNode* Find(char* name);
	void Remove(MonsterNode* mn);
	int SamePositionAmount();
	void MonstersAct();
	bool Encountered(Engine::Point2D p);
	void Print();
};

