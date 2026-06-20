#include "Monster.h"
#include <iostream>

Monster::Monster(std::string n, int h, int d, int reward)
    : Character(n, h, d), expReward(reward), maxHealth(h) {}

void Monster::attack(Character& target) {
    std::cout << "Монстр " << name << " свирепо атакует!\n";
    target.takeDamage(damage); 
}

int Monster::getExpReward() const { return expReward; }
int Monster::getMaxHealth() const { return maxHealth; }
