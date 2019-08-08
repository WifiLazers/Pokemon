#pragma once
#include <string>
#include "Pokemon.h"

enum class ItemType { RestoreHP, Revive, CurePoison, CureParalysis, CureConfusion, Wake, CureBurn, Defrost, Attack, Defense, SpecialAttack, SpecialDefense, Speed, None };

class Item
{
public:
	Item();
	Item(std::string n, int p, ItemType t);
	std::string name_;
	int power_;
	ItemType type_;
	
};

