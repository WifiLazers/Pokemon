#include "Pokemon.h"
#include "Item.h"
#include "Effect.h"
#include "Trainer.h"
#include "Move.h"
#include "Battle.h"

Item Potion("Potion", 30, ItemType::RestoreHP);
Item HyperPotion("Hyper Potion", 200, ItemType::RestoreHP);
Item Antidote("Antidote", 0, ItemType::CurePoison);
Item ParalyzeHeal("Paralyze Heal", 0, ItemType::CureParalysis);
Item Awakening("Awakening", 0, ItemType::Wake);
Item BurnHeal("Burn Heal", 0, ItemType::CureBurn);
Item IceHeal("Ice Heal", 0, ItemType::Defrost);
Item PersimBerry("Persim Berry", 0, ItemType::CureConfusion);
Item Revive("Revive", 0, ItemType::Revive);
Item Protein("Protein", 10, ItemType::Attack);
Item Iron("Iron", 10, ItemType::Defense);
Item Calcium("Calcium", 10, ItemType::SpecialAttack);
Item Zinc("Zinc", 10, ItemType::SpecialDefense);

std::vector<Item> ashitems = { Potion, Potion, Potion, Protein, Protein, Protein, Iron, Iron, Calcium, PersimBerry };
std::vector<Item> reditems = { Potion, Protein, Iron, HyperPotion, Revive, ParalyzeHeal };

Move WaterPulse("Water Pulse", 60, 100, 20, 0, Type::Water, MoveCategory::Special, { Effect::None }, 0, 0, "");
Move DoubleTeam("Double Team", 0, 100, 15, 1, Type::Normal, MoveCategory::Status, { Effect::Evasiveness }, 100, 10, "");
Move HydroPump("Hydro Pump", 110, 80, 5, 0, Type::Water, MoveCategory::Special, { Effect::None }, 0, 0, "");
Move NightSlash("Night Slash", 70, 100, 15, 0, Type::Dark, MoveCategory::Physical, { Effect::None }, 0, 0, "");

std::vector<Move> GreninjaAttacks = { WaterPulse, DoubleTeam, HydroPump, NightSlash };

Pokemon Greninja("Greninja", 50, 179, 216, 130, 225, 135, 202, Type::Water, Type::Dark, GreninjaAttacks);

Move DragonBreath("Dragon Breath", 60, 100, 20, 0, Type::Dragon, MoveCategory::Special, { Effect::Paralyze }, 30, 0, "");
Move DragonPulse("Dragon Pulse", 85, 100, 10, 0, Type::Dragon, MoveCategory::Special, { Effect::None }, 0, 0, "");
Move Moonblast("Moonblast", 95, 100, 15, 0, Type::Fairy, MoveCategory::Special, { Effect::SpecialAttack }, 30, -10, "");
Move SkyAttack("Sky Attack", 140, 90, 5, 0, Type::Flying, MoveCategory::Physical, { Effect::None }, 0, 0, "");

std::vector<Move> AltariaAttacks = { DragonBreath, DragonPulse, Moonblast, SkyAttack };

Pokemon Altaria("Altaria", 50, 182, 178, 178, 178, 172, 45, Type::Dragon, Type::Flying, AltariaAttacks);

Move SludgeBomb("Sludge Bomb", 90, 100, 10, 0, Type::Poison, MoveCategory::Special, { Effect::Poison }, 30, 0, "");
Move Screech("Screech", 0, 85, 20, 0, Type::Poison, MoveCategory::Status, { Effect::Defense }, 100, -20, "");
Move Toxic("Toxic", 0, 90, 10, 0, Type::Poison, MoveCategory::Status, { Effect::Poison }, 100, 0, "");
Move AcidArmor("Acid Armor", 0, 100, 20, 0, Type::Poison, MoveCategory::Status, { Effect::Defense }, 100, 20, "");

std::vector<Move> MukAttacks = { SludgeBomb, Screech, Toxic, AcidArmor };

Pokemon Muk("Muk", 50, 212, 172, 139, 128, 167, 112, Type::Poison, Type::None, MukAttacks);


Move Dig("Dig", 80, 100, 10, 1, Type::Ground, MoveCategory::Physical, { Effect::Hide }, 100, 2, " dug a hole in the ground!");
Move Earthquake("Earthquake", 100, 100, 10, 0, Type::Ground, MoveCategory::Physical, { Effect::None }, 0, 0, "");
Move Fissure("Fissure", 0, 30, 5, 0, Type::Ground, MoveCategory::Physical, { Effect::KO }, 100, 0, "");
Move SuckerPunch("Sucker Punch", 70, 100, 5, 0, Type::Ground, MoveCategory::Physical, { Effect::None }, 0, 0, "");

std::vector<Move> DugtrioAttacks = { Dig, Earthquake, Fissure, SuckerPunch };

Pokemon Dugtrio("Dugtrio", 50, 142, 167, 112, 112, 134, 189, Type::Ground, Type::None, DugtrioAttacks);

Move Confusion("Confusion", 50, 100, 25, 0, Type::Psychic, MoveCategory::Special, { Effect::Confuse }, 30, 0, "");
Move Hypnosis("Hypnosis", 0, 60, 20, 0, Type::Psychic, MoveCategory::Special, { Effect::Sleep }, 100, 0, "");
Move DreamEater("Dream Eater", 100, 100, 15, 0, Type::Psychic, MoveCategory::Special, { Effect::None }, 100, 0, "");
Move FutureSight("Future Sight", 120, 100, 10, 1, Type::Psychic, MoveCategory::Special, { Effect::Charge }, 100, 3, " foresaw the future!");

std::vector<Move> GardevoirAttacks = { Confusion, Hypnosis, DreamEater, FutureSight };

Pokemon Gardevoir("Gardevoir", 50, 175, 128, 128, 194, 183, 145, Type::Psychic, Type::Fairy, GardevoirAttacks);

std::vector<Pokemon> AshPokemon = { Altaria, Gardevoir, Dugtrio };

Trainer Ash("Ash", &AshPokemon, ashitems);

std::vector<Pokemon> RedPokemon = { Dugtrio, Greninja, Muk };

Trainer Red("Red", &RedPokemon, reditems);


int main()
{
	Battle battle(&Ash, &Red);
	

	battle.MainBattleLoop();
	
}