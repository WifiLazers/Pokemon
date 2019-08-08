#include "Trainer.h"

Trainer::Trainer() : name_(""), pokemons_(nullptr) {};

Trainer::Trainer(std::string n, std::vector<Pokemon>* p, std::vector<Item> i) : name_(n), pokemons_(p), items_(i) {};
