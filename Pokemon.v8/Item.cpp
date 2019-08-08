#include <iostream>
#include "Item.h"

Item::Item() : name_(""), power_(0), type_(ItemType::None) {};
Item::Item(std::string n, int p, ItemType t) : name_(n), power_(p), type_(t) {}