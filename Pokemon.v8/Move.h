#pragma once
#include <string>
#include <vector>
#include "Type.h"
#include "Effect.h"

enum class MoveCategory { Status, Physical, Special };
enum class Special {Stats, Condition, None};

class Move
{
public:
	Move();
	Move(std::string n, float p, int a, int pp, int pri, Type t, MoveCategory c, std::vector<Effect> e, int ec, int ea, std::string Special);
	std::string name_;
	float power_;
	int accuracy_;
	int power_points_;
	int current_PP_;
	int priority;
	Type type_;
	MoveCategory category_;
	std::vector<Effect> effect_;
	int effect_chance_;
	int effect_amount_;
	std::string SpecialEffect;


};

