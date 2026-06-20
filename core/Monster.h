#pragma once
#include "Character.h"

class Monster : public Character {
private:
    int expReward;
    int maxHealth;

public:
    Monster(std::string n, int h, int d, int reward);
    void attack(Character& target) override;
    int getExpReward() const;
    int getMaxHealth() const;
};
