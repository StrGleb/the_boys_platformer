#include "Player.h"
#include <iostream>
#include <cstdlib>

Player::Player(std::string n, int h, int d, std::string cName)
    : Character(n, h, d), className(cName), exp(0), maxHealth(h),
      abilityCooldown(0), knightDefendTurns(0), mageShieldActive(false), archerFocusActive(false) {
    inventory.addItem(Item("Малое_зелье", "potion", 30));
}

void Player::attack(Character& target) {
    int finalDamage = damage;
    bool isCrit = (std::rand() % 5 == 0) || archerFocusActive;
    
    if (archerFocusActive) {
        std::cout << "★ Точный выстрел Лучника! ★\n";
        archerFocusActive = false;
    } else if (isCrit) {
        std::cout << "★ КРИТИЧЕСКИЙ УДАР! ★\n";
    }
    if (isCrit) finalDamage *= 2;

    std::cout << className << " " << name << " наносит " << finalDamage << " урона!\n";
    target.takeDamage(finalDamage);
}

void Player::useAbility(Character& target) {
    if (abilityCooldown > 0) {
        std::cout << "Навык еще перезаряжается! Осталось ходов: " << abilityCooldown << "\n";
        return;
    }
    if (className == "Рыцарь") {
        std::cout << name << " поднимает щит! Активирована Стена щитов!\n";
        knightDefendTurns = 2;
    } else if (className == "Маг") {
        std::cout << name << " зажигает Магический барьер!\n";
        mageShieldActive = true;
    } else if (className == "Лучник") {
        std::cout << name << " концентрируется на цели! Следующий удар будет критическим!\n";
        archerFocusActive = true;
    }
    abilityCooldown = 4; 
}

void Player::customTakeDamage(int amount, Character& target) {
    if (className == "Рыцарь" && knightDefendTurns > 0) {
        if (knightDefendTurns == 2) {
            std::cout << "Щит полностью поглотил урон монстра (100% блок)!\n";
            amount = 0;
        } else if (knightDefendTurns == 1) {
            std::cout << "Щит поглотил половину урона (50% блок)!\n";
            amount /= 2;
        }
    } else if (className == "Маг" && mageShieldActive) {
        std::cout << "Магический барьер взрывается и поглощает весь урон!\n";
        std::cout << "Энергия барьера бьет в ответ по " << target.getName() << " на 15 урона!\n";
        target.takeDamage(15);
        mageShieldActive = false;
        amount = 0;
    } else if (className == "Лучник" && (std::rand() % 100 < 40)) {
        std::cout << name << " грациозно уклоняется от атаки!\n";
        amount = 0;
    }
    takeDamage(amount);
}

void Player::updateCooldowns() {
    if (abilityCooldown > 0) abilityCooldown--;
    if (knightDefendTurns > 0) knightDefendTurns--;
}

void Player::gainExp(int amount) {
    exp += amount;
    std::cout << name << " получает " << amount << " опыта! Всего опыта: " << exp << "\n";
    if (exp >= 100) {
        exp = 0;
        damage += 4;
        maxHealth += 15;
        health = maxHealth;
        std::cout << "Уровень повышен! Атака и здоровье увеличены!\n";
    }
}

void Player::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
    std::cout << name << " восстанавливает " << amount << " HP. Текущее HP: " << health << "\n";
}

void Player::addDamage(int amount) {
    damage += amount;
    std::cout << "Ваша базовая атака увеличилась на " << amount << "! Текущая атака: " << damage << "\n";
}

bool Player::pickUpItem(const Item& item) { return inventory.addItem(item); }

void Player::openInventory() {
    if (inventory.isEmpty()) {
        std::cout << "Инвентарь пуст!\n";
        return;
    }
    std::cout << "\n--- ИНВЕНТАРЬ ---\n";
    inventory.printInventory();
    std::cout << "0. Назад\nВыберите номер: ";
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < 0 || choice > static_cast<int>(inventory.getSize())) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный выбор слота! Попробуйте снова: ";
        } else {
            std::cin.ignore(10000, '\n');
            break;
        }
    }
    if (choice > 0) {
        Item selected = inventory.getItem(choice - 1);
        if (selected.getType() == "potion") {
            heal(selected.getValue());
            inventory.removeItem(choice - 1);
        } else if (selected.getType() == "weapon") {
            addDamage(selected.getValue());
            inventory.removeItem(choice - 1);
        }
    }
}

std::string Player::getClassName() const { return className; }
int Player::getExp() const { return exp; }
int Player::getMaxHealth() const { return maxHealth; }
int Player::getCooldown() const { return abilityCooldown; }
