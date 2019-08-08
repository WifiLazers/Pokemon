#include "Pokemon.h"


Pokemon::Pokemon() : name_("Missingno"), level_(0), maxhealth_(0), currenthealth_(0), attack_(0), defense_(0), specialattack_(0), specialdefense_(0), speed_(0), primary_type_(Type::None), secondary_type_(Type::None), PrimaryWeakToList({}), PrimaryResistantToList({}), PrimaryImmuneToList({}), SecondaryWeakToList({}), SecondaryResistantToList({}), SecondaryImmuneToList({}), AttackList({}) {}
Pokemon::Pokemon(std::string n, int l, float mh, float a, float d, float sa, float sd, float s, Type pt, Type st, std::vector<Move> alist) :
	name_(n), level_(l), maxhealth_(mh), currenthealth_(mh), attack_(a), defense_(d), specialattack_(sa), specialdefense_(sd), speed_(s), primary_type_(pt), secondary_type_(st), AttackList(alist)
{
	PrimaryWeakToList = GetWeakness(pt);
	PrimaryResistantToList = GetResistance(pt);
	PrimaryImmuneToList = GetImmune(pt);
	SecondaryWeakToList = GetWeakness(st);
	SecondaryResistantToList = GetResistance(st);
	SecondaryImmuneToList = GetImmune(st);
}
std::vector<Type> Pokemon::GetWeakness(Type type)
{
	std::vector<Type> wlist;
	if (type == Type::Fire) {
		wlist = { Type::Water, Type::Rock, Type::Ground };
	}
	else if (type == Type::Water) {
		wlist = { Type::Electric, Type::Grass };
	}
	else if (type == Type::Electric) {
		wlist = { Type::Ground };
	}
	else if (type == Type::Ground) {
		wlist = { Type::Water, Type::Grass };
	}
	else if (type == Type::Grass) {
		wlist = { Type::Fire, Type::Poison, Type::Flying };
	}
	else if (type == Type::Normal) {
		wlist = { Type::Fighting };
	}
	else if (type == Type::Psychic) {
		wlist = { Type::Fighting, Type::Psychic };
	}
	else if (type == Type::Fighting) {
		wlist = { Type::Bug, Type::Rock };
	}
	else if (type == Type::Flying) {
		wlist = { Type::Bug, Type::Fighting, Type::Grass };
	}
	else if (type == Type::Bug) {
		wlist = { Type::Fire, Type::Flying, Type::Poison, Type::Rock };
	}
	else if (type == Type::Rock) {
		wlist = { Type::Fighting, Type::Grass, Type::Water, Type::Ground };
	}
	else if (type == Type::Ice) {
		wlist = { Type::Fighting, Type::Fire, Type::Rock };
	}
	else if (type == Type::Poison) {
		wlist = { Type::Ground, Type::Bug, Type::Psychic };
	}
	else if (type == Type::Dragon) {
		wlist = { Type::Dragon, Type::Ice };
	}
	else if (type == Type::Ghost) {
		wlist = { Type::Ghost, Type::Dark };
	}
	else if (type == Type::Dark) {
		wlist = { Type::Bug, Type::Fighting };
	}
	else if (type == Type::Steel) {
		wlist = { Type::Fighting, Type::Fire, Type::Ground };
	}
	else if (type == Type::Fairy) {
		wlist = { Type::Poison, Type::Steel };
	}
	else if (type == Type::None) {
		wlist = {};
	}
	return wlist;
}
std::vector<Type> Pokemon::GetResistance(Type type)
{
	std::vector<Type> rlist;
	if (type == Type::Fire) {
		rlist = { Type::Bug, Type::Fire, Type::Grass };
	}
	else if (type == Type::Water) {
		rlist = { Type::Fire, Type::Water };
	}
	else if (type == Type::Electric) {
		rlist = { Type::Electric, Type::Flying };
	}
	else if (type == Type::Ground) {
		rlist = { Type::Poison, Type::Rock };
	}
	else if (type == Type::Grass) {
		rlist = { Type::Electric, Type::Grass, Type::Ground, Type::Water };
	}
	else if (type == Type::Normal) {
		rlist = { Type::None };
	}
	else if (type == Type::Psychic) {
		rlist = { Type::Bug };
	}
	else if (type == Type::Fighting) {
		rlist = { Type::Bug, Type::Rock };
	}
	else if (type == Type::Flying) {
		rlist = { Type::Bug, Type::Fighting, Type::Grass };
	}
	else if (type == Type::Bug) {
		rlist = { Type::Fighting, Type::Grass, Type::Ground };
	}
	else if (type == Type::Rock) {
		rlist = { Type::Fire, Type::Flying, Type::Normal, Type::Poison };
	}
	else if (type == Type::Poison) {
		rlist = { Type::Fighting, Type::Poison, Type::Grass };
	}
	else if (type == Type::Dragon) {
		rlist = { Type::Electric, Type::Fire, Type::Grass, Type::Water };
	}
	else if (type == Type::Ghost) {
		rlist = { Type::Bug, Type::Poison };
	}
	else if (type == Type::Dark) {
		rlist = { Type::Dark, Type::Ghost };
	}
	else if (type == Type::Steel) {
		rlist = { Type::Bug, Type::Dark, Type::Dragon, Type::Flying, Type::Fairy, Type::Grass, Type::Ice, Type::Normal, Type::Psychic, Type::Rock, Type::Steel };
	}
	else if (type == Type::Fairy) {
		rlist = { Type::Bug, Type::Dark, Type::Fighting };
	}
	else if (type == Type::None) {
		rlist = {};
	}
	return rlist;
}
std::vector<Type> Pokemon::GetImmune(Type type)
{
	std::vector<Type> ilist;

	if (type == Type::Ghost) {
		ilist = { Type::Normal, Type::Fighting };
	}
	else if (type == Type::Ground) {
		ilist = { Type::Electric };
	}
	else if (type == Type::Flying) {
		ilist = { Type::Ground };
	}
	else if (type == Type::Dark) {
		ilist = { Type::Psychic };
	}
	else if (type == Type::Steel) {
		ilist = { Type::Poison };
	}
	else if (type == Type::Fairy) {
		ilist = { Type::Dragon };
	}
	else {
		ilist = { Type::None };
	}
	return ilist;
}

void Pokemon::Summary()
{
	std::cout << name_ << " Stats:" << std::endl;
	std::cout << std::endl;
	std::cout << "Name: " << name_ << std::endl;
	std::cout << "Attack: " << attack_ << std::endl;
	std::cout << "Defense: " << defense_ << std::endl;
	std::cout << "Special Attack : " << specialattack_ << std::endl;
	std::cout << "Special Defense: " << specialdefense_ << std::endl;
	std::cout << "Speed: " << speed_ << std::endl;
	std::cout << std::endl;
	std::cout << "Attacks: " << std::endl;
	for (size_t i = 0; i < AttackList.size(); i++)
	{
		std::cout << (i + 1) << ". " << AttackList[i].name_ << " " << AttackList[i].current_PP_ << "/" << AttackList[i].power_points_ << std::endl;
	}
	std::cout << std::endl;
}

