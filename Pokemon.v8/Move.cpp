#include "Move.h"

Move::Move() : name_("none"), power_(40), accuracy_(0), power_points_(0), current_PP_(0), priority(0), type_(Type::None), category_(MoveCategory::Status), effect_({ Effect::None }), effect_chance_(0), effect_amount_(0), SpecialEffect("") {};
Move::Move(std::string n, float p, int a, int pp, int pri, Type t, MoveCategory c, std::vector<Effect> e, int ec, int ea, std::string Special) : name_(n), power_(p), accuracy_(a), power_points_(pp), current_PP_(pp), priority(pri), type_(t), category_(c), effect_(e), effect_chance_(ec), effect_amount_(ea), SpecialEffect(Special) {}


