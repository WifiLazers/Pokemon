#pragma once
#include "Trainer.h"
#include "Pokemon.h"
#include "Move.h"
#include "Item.h"

class Battle
{
public:
	Battle(Trainer* p, Trainer* o);
	Trainer* player_;
	Trainer* opponent_;
	std::vector<Pokemon>* player_pokemons_ = player_->pokemons_;
	std::vector<Pokemon>* opponent_pokemons_ = opponent_->pokemons_;
	Pokemon* player_pokemon_ = &(player_pokemons_->at(0));
	Pokemon* opponent_pokemon_ = &(opponent_pokemons_->at(0));
	Move* player_move_ = nullptr;
	Move* opponent_move_ = nullptr;
	Item* player_item_ = nullptr;
	Item* opponent_item = nullptr;
	Pokemon* player_item_pokemon = nullptr;
	Pokemon* opponent_item_pokemon = nullptr;
	Move* player_future_move_ = nullptr;
	Move* opponent_future_move_ = nullptr;

	Pokemon* player_next_pokemon_ = nullptr;
	Pokemon* opponent_next_pokemon_ = nullptr;
	
	void Intro();
	void ShowStatus();
	int MainMenu();
	bool UserNoMorePokemon();
	bool OpponentNoMorePokemon();
	void MainBattleLoop();

	void SwitchPokemon();
	void SwitchDeclaration();
	void OpponentSwitchPokemon();
	void CalculatePriority(Move* playermove, Move* opponentmove);
	void BattleLoop();
	void PlayerWaits();
	void UserMakesChoice();
	void OpponentMakesChoice();
	void UserChooseMove(); //remove stupid shit
	void OpponentChooseMove();
	void RemoveStatus(Status status, Pokemon* pokemon);
	bool DetermineEffect(Move* move, Pokemon* attacking, Pokemon* defending);
	void ExcessDamage(Pokemon* attacking);
	void EndEffect(Move* move, Pokemon* attacking, Pokemon* defending);
	bool CheckIfHit(Move* move, Pokemon* defending);
	void UseMove(Move* move, Pokemon* attacking, Pokemon* defending);
	float CalculateModifier(Move* move, Pokemon* defending);
	float CalculateDamage(Move* move, Pokemon* attacking, Pokemon* defending);
	void ChooseItem();
	void UseItem(Item* item, Trainer* trainer, Pokemon* pokemon);
	void OpponentChooseItem();
};