#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Type.h"
#include "Status.h"
#include "Move.h"

class Pokemon
{
public:
	Pokemon();
	Pokemon(std::string n, int l, float mh, float a, float d, float sa, float sd, float s, Type pt, Type st, std::vector<Move> alist);
	std::string name_;
	int level_;
	float maxhealth_;
	float currenthealth_;
	float attack_;
	float defense_;
	float specialattack_;
	float specialdefense_;
	float speed_;
	float evasion_ = 0;
	bool active_ = false;
	bool visible_ = true;
	int attackcounter = 0;
	int effectcounter = 0;
	int statuscounter = 0;
	Move* future_move_ = nullptr;

	//a pokemon can be confused and poisoned at the same time! i think.
	std::vector<Status> status_ = { Status::Normal };
	Type primary_type_;
	Type secondary_type_;
	std::vector<Type> PrimaryWeakToList;
	std::vector<Type> PrimaryResistantToList;
	std::vector<Type> PrimaryImmuneToList;
	std::vector<Type> SecondaryWeakToList;
	std::vector<Type> SecondaryResistantToList;
	std::vector<Type> SecondaryImmuneToList;
	std::vector<Move> AttackList;

	std::vector<Type> GetWeakness(Type type);
	std::vector<Type> GetResistance(Type type);
	std::vector<Type> GetImmune(Type type);

	void Summary();
};

