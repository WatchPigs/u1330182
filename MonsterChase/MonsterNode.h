#pragma once
#include "Monster.h"
 
struct MonsterNode
{
	Monster* self;
	MonsterNode* last;
	MonsterNode* next;
};

