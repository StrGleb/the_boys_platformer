#include "Character.h"
#include <iostream>
#include <cstdlib>

Character::Character(std::string n, int h, int d) 
    : name(n), health(h), damage(d) {}

void Character::attack(Character& target) {
    int finalDamage = damage;
    bool isCrit = (std::rand() % 5 == 0); 
    if (isCrit) {
        std::cout << "★ КРИТИЧЕСКИЙ УДАР! ★\n";
        finalDamage *= 2;
    }
    std::cout << name << " атакует " << target.getName() << " и наносит " << finalDamage << " урона!\n";
    target.takeDamage(finalDamage);
}

void Character::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
    std::cout << name << " теряет " << amount << " HP. Осталось: " << health << " HP.\n";
}

bool Character::isAlive() const { return health > 0; }
std::string Character::getName() const { return name; }
int Character::getHealth() const { return health; }
int Character::getDamage() const { return damage; }
