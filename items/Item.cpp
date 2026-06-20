#include "Item.h"

Item::Item() : name("Пусто"), type("none"), value(0) {}
Item::Item(std::string n, std::string t, int v) : name(n), type(t), value(v) {}
std::string Item::getName() const { return name; }
std::string Item::getType() const { return type; }
int Item::getValue() const { return value; }
