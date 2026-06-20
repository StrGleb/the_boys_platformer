#pragma once
#include <string>

class Character {
protected:
    std::string name;
    int health;
    int damage;

public:
    Character(std::string n, int h, int d);
    virtual void attack(Character& target);
    void takeDamage(int amount);
    bool isAlive() const;

    std::string getName() const;
    int getHealth() const;
    int getDamage() const;
    virtual ~Character() = default;
};
