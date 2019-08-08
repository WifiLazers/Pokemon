#pragma once
#include <string>
#include <vector>
#include "Pokemon.h"
#include "Item.h"

class Trainer
{
public:
	Trainer();
	Trainer(std::string n, std::vector<Pokemon>* p, std::vector<Item> i);
	std::string name_;
	std::vector<Pokemon>* pokemons_;
	std::vector<Item> items_;
	
};

