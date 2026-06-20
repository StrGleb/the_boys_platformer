#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>
#include <vector>
#include <clocale>

#include "core/Player.h"
#include "core/Monster.h"
#include "items/Item.h"
#include "graphics/Renderer.h"
#include "scores/Highscores.h"


struct MonsterData {
    std::string name;
    int hp, dmg, exp;
};

void waitEnter() {
    std::cout << "\n[Нажмите Enter, чтобы продолжить...]";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int getSafeInput(int minVal, int maxVal) {
    int choice;
    while (true) {
        std::cin >> choice;
        
        if (std::cin.fail() || choice < minVal || choice > maxVal) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод! Выберите число от " << minVal << " до " << maxVal << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

std::vector<Item> loadItems() {
    std::vector<Item> items;
    std::ifstream file("config/items.txt"); 
    std::string name, type;
    int val;
    while (file >> name >> type >> val) {
        items.push_back(Item(name, type, val));
    }
    return items;
}

std::vector<MonsterData> loadMonsters() {
    std::vector<MonsterData> monsters;
    std::ifstream file("config/monsters.txt"); 
    std::string name;
    int hp, dmg, exp;
    while (file >> name >> hp >> dmg >> exp) {
        monsters.push_back({name, hp, dmg, exp});
    }
    return monsters;
}


int main() {
    std::setlocale(LC_ALL, "");
    std::ios_base::sync_with_stdio(false);
    std::srand(std::time(0));

    std::vector<Item> configItems = loadItems();
    std::vector<MonsterData> configMonsters = loadMonsters();

    Renderer::clearScreen();
    std::cout << "=======================================================\n";
    std::cout << "                СПАСЕНИЕ КОРОЛЯ-ОТЦА                   \n";
    std::cout << "=======================================================\n\n";
    std::cout << "Твой родной замок захвачен монстрами. Спаси короля-отца!\n\n";

    std::cout << "Введите имя вашего героя: ";
    std::string heroName;
    std::getline(std::cin, heroName);

    std::cout << "\nВыберите класс персонажа:\n";
    std::cout << "1. Рыцарь (110 HP, 12 Урон)\n";
    std::cout << "2. Маг (65 HP, 25 Урон)\n";
    std::cout << "3. Лучник (85 HP, 17 Урон)\n";
    std::cout << "Выбор: ";
    
    int classChoice = getSafeInput(1, 3);

    std::string className = "Рыцарь";
    int heroHP = 110, heroDamage = 12;

    if (classChoice == 2) {
        className = "Маг"; heroHP = 65; heroDamage = 25;
    } else if (classChoice == 3) {
        className = "Лучник"; heroHP = 85; heroDamage = 17;
    }

    Player hero(heroName, heroHP, heroDamage, className);
    std::cout << "\nВы создали персонажа: " << hero.getClassName() << " " << hero.getName() << "!\n";
    Renderer::sleep(1500);

    int currentLevel = 2;

    while (hero.isAlive() && currentLevel <= 10) {
        if (currentLevel >= 2 && currentLevel <= 8) {
            int eventType = std::rand() % 3;

            if (eventType == 0 || eventType == 1) {
                if (configMonsters.empty()) break;
                int idx = std::rand() % configMonsters.size();
                MonsterData mData = configMonsters[idx];

                int mHP = mData.hp + (currentLevel * 3);
                int mDmg = mData.dmg + (currentLevel * 1);
                Monster enemy(mData.name, mHP, mDmg, mData.exp);

                while (hero.isAlive() && enemy.isAlive()) {
                    Renderer::clearScreen();
                    Renderer::drawBattleScene(hero.getClassName(), hero.getName(), hero.getHealth(), hero.getMaxHealth(), enemy.getName(), enemy.getHealth(), enemy.getMaxHealth());
                    
                    std::cout << "Ваш ход:\n1. Атаковать\n2. Открыть инвентарь\n3. Особый навык (Откат: " << hero.getCooldown() << ")\nВыбор: ";
                    int action = getSafeInput(1, 3);

                    if (action == 1) {
                        Renderer::clearScreen();
                        Renderer::drawPlayerAttackScene(hero.getClassName(), hero.getName(), hero.getHealth(), hero.getMaxHealth(), enemy.getName(), enemy.getHealth(), enemy.getMaxHealth());
                        std::cout << "\n";
                        hero.attack(enemy);
                        waitEnter();
                    } else if (action == 2) {
                        Renderer::clearScreen();
                        hero.openInventory();
                        waitEnter();
                    } else if (action == 3) {
                        Renderer::clearScreen();
                        hero.useAbility(enemy);
                        waitEnter();
                    }

                    if (enemy.isAlive()) {
                        Renderer::clearScreen();
                        Renderer::drawMonsterAttackScene(hero.getClassName(), hero.getName(), hero.getHealth(), hero.getMaxHealth(), enemy.getName(), enemy.getHealth(), enemy.getMaxHealth());
                        std::cout << "\n";
                        
                        hero.customTakeDamage(enemy.getDamage(), enemy);
                        hero.updateCooldowns();
                        waitEnter();
                    }
                }

                if (hero.isAlive()) {
                    Renderer::clearScreen();
                    std::cout << "Вы одолели противника!\n";
                    hero.gainExp(enemy.getExpReward());
                    waitEnter();
                }
            } 
            else {
                Renderer::clearScreen();
                Renderer::drawChestScene(hero.getClassName(), false);
                std::cout << "\nВы обнаружили королевский сундук!\n";
                waitEnter();

                Renderer::clearScreen();
                Renderer::drawChestScene(hero.getClassName(), true);
                std::cout << "\n";

                if (!configItems.empty()) {
                    int randIdx = std::rand() % configItems.size();
                    Item loot = configItems[randIdx];
                    std::cout << "Вы нашли предмет: " << loot.getName() << "!\n";
                    hero.pickUpItem(loot);
                }
                waitEnter();
            }
        }
        else if (currentLevel == 9) {
            Monster boss("Дракон-Страж", 170, 24, 0);

            while (hero.isAlive() && boss.isAlive()) {
                Renderer::clearScreen();
                Renderer::drawDragonScene(hero.getClassName(), hero.getName(), hero.getHealth(), hero.getMaxHealth(), boss.getName(), boss.getHealth(), boss.getMaxHealth());
                
                std::cout << "ФИНАЛЬНЫЙ БОЙ!\n1. Атаковать\n2. Открыть инвентарь\n3. Особый навык\nВыбор: ";
                int action = getSafeInput(1, 3);

                if (action == 1) {
                    Renderer::clearScreen();
                    Renderer::drawDragonPlayerAttack(hero.getClassName(), hero.getName(), hero.getHealth(), hero.getMaxHealth(), boss.getName(), boss.getHealth(), boss.getMaxHealth());
                    std::cout << "\n";
                    hero.attack(boss);
                    waitEnter();
                } else if (action == 2) {
                    Renderer::clearScreen();
                    hero.openInventory();
                    waitEnter();
                } else if (action == 3) {
                    Renderer::clearScreen();
                    hero.useAbility(boss);
                    waitEnter();
                }

                if (boss.isAlive()) {
                    Renderer::clearScreen();
                    Renderer::drawDragonMonsterAttack(hero.getClassName(), hero.getName(), hero.getHealth(), hero.getMaxHealth(), boss.getName(), boss.getHealth(), boss.getMaxHealth());
                    std::cout << "\n";
                    hero.customTakeDamage(boss.getDamage(), boss);
                    hero.updateCooldowns();
                    waitEnter();
                }
            }

            if (hero.isAlive()) {
                Renderer::clearScreen();
                std::cout << "Дракон с грохотом падает на плиты тронного зала.\n";
                waitEnter();
            }
        }
        else if (currentLevel == 10) {
            Renderer::clearScreen();
            Renderer::drawCrown();
            std::cout << "\nКороль: \"Спасибо, мой отважный сын " << hero.getName() << "! Ты спас меня!\"\n\n";
            std::cout << "=======================================================\n";
            std::cout << "            ПОЗДРАВЛЯЕМ! ИГРА ПРОЙДЕНА!                \n";
            std::cout << "=======================================================\n";
            waitEnter();
        }

        if (hero.isAlive()) currentLevel++;
    }

    if (!hero.isAlive()) {
        Renderer::clearScreen();
        std::cout << "Вы пали в бою... Спасти Короля-отца не удалось.\n";
        waitEnter();
    }

    Renderer::clearScreen();
    
    int finalScore = hero.getExp() * 3; 

    if (hero.isAlive()) finalScore += 500; 

    Highscores leaderboard;
    leaderboard.addScore(hero.getName(), finalScore);
    
    leaderboard.printScores();
    
    waitEnter();

    return 0;
}
