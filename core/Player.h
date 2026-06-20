#pragma once
#include "Character.h"
#include "../items/Inventory.h"

class Player : public Character {
private:
    std::string className;
    int exp;
    int maxHealth;
    Inventory inventory;
    
    int abilityCooldown;
    int knightDefendTurns; 
    bool mageShieldActive;
    bool archerFocusActive;

public:
    Player(std::string n, int h, int d, std::string cName);
    void attack(Character& target) override;
    void useAbility(Character& target);
    void updateCooldowns();
    
    void gainExp(int amount);
    void heal(int amount);
    void addDamage(int amount);
    void customTakeDamage(int amount, Character& target);

    bool pickUpItem(const Item& item);
    void openInventory();

    std::string getClassName() const;
    int getExp() const;
    int getMaxHealth() const;
    int getCooldown() const;
};
