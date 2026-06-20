#include "Renderer.h"
#include <iostream>
#include <thread>
#include <chrono>

void Renderer::clearScreen() { std::cout << "\033[2J\033[1;1H"; }
void Renderer::sleep(int milliseconds) { std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)); }

void Renderer::drawHealthBars(const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP) {
    int pBars = (pMaxHP > 0) ? (pHP * 10) / pMaxHP : 0;
    int mBars = (mMaxHP > 0) ? (mHP * 10) / mMaxHP : 0;

    int baseHP = (pName.find("Маг") != std::string::npos) ? 65 : ((pName.find("Лучник") != std::string::npos) ? 85 : 110);
    int currentLvl = 1 + (pMaxHP - baseHP) / 15;
    if (currentLvl < 1) currentLvl = 1;

    std::cout << " " << pName << " [Lvl " << currentLvl << "]" << "               " << mName << "\n";
    std::cout << " [";
    for (int i = 0; i < 10; ++i) std::cout << (i < pBars ? "I" : ".");
    std::cout << "] " << pHP << "/" << pMaxHP << " HP    VS    [";
    for (int i = 0; i < 10; ++i) std::cout << (i < mBars ? "I" : ".");
    std::cout << "] " << mHP << "/" << mMaxHP << " HP\n";
    std::cout << "=======================================================\n\n";
}

void Renderer::drawBattleScene(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP) {
    drawHealthBars(pName, pHP, pMaxHP, mName, mHP, mMaxHP);
    if (pClass == "Маг") {
        std::cout << "     /\\                                /\\_/\\ \n";
        std::cout << "    (o.o)--*                          ( -.- ) \n";
        std::cout << "    / | \\                              / | \\  \n";
        std::cout << "    _/_\\_                             _/_\\_  \n";
    } else if (pClass == "Лучник") {
        std::cout << "    }-)                                /\\_/\\ \n";
        std::cout << "    (o.o)====>                        ( -.- ) \n";
        std::cout << "    / | \\                              / | \\  \n";
        std::cout << "    _/_\\_                             _/_\\_  \n";
    } else { 
        std::cout << "    [===]                              /\\_/\\ \n";
        std::cout << "    (o.o)-====>                       ( -.- ) \n";
        std::cout << "    /[ ]\\                              / | \\  \n";
        std::cout << "    _/_\\_                             _/_\\_  \n";
    }
    std::cout << "=======================================================\n";
}

void Renderer::drawPlayerAttackScene(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP) {
    drawHealthBars(pName, pHP, pMaxHP, mName, mHP, mMaxHP);
    if (pClass == "Маг") {
        std::cout << "         /\\        *БАМХ*              /\\_/\\ \n";
        std::cout << "        (o.o)======>                  ( >_< ) \n";
        std::cout << "        / | \\                          / | \\  \n";
        std::cout << "        _/_\\_                         _/_\\_  \n";
    } else if (pClass == "Лучник") {
        std::cout << "               }-)     *ВЖУХ!*         /\\_/\\ \n";
        std::cout << "               (o.o)====>             ( >_< ) \n";
        std::cout << "               / | \\                          / | \\  \n";
        std::cout << "               _/_\\_                         _/_\\_  \n";
    } else {
        std::cout << "               [===]===> *БЕМС*        /\\_/\\ \n";
        std::cout << "               (o.o)                  ( >_< ) \n";
        std::cout << "               /[ ]\\                   / | \\  \n";
        std::cout << "               _/_\\_                  _/_\\_  \n";
    }
    std::cout << "=======================================================\n";
}

void Renderer::drawMonsterAttackScene(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP) {
    drawHealthBars(pName, pHP, pMaxHP, mName, mHP, mMaxHP);
    std::cout << "     " << (pClass == "Рыцарь" ? "[===]" : " /\\ ") << "               *ХРЯСЬ*          /\\_/\\ \n";
    std::cout << "    ( >_< )                   <========(o.o)  \n";
    std::cout << "    / | \\                              / | \\  \n";
    std::cout << "    _/_\\_                             _/_\\_  \n";
    std::cout << "=======================================================\n";
}

void Renderer::drawChestScene(const std::string& pClass, bool isOpen) {
    std::cout << "=======================================================\n";
    std::cout << "               КОРОЛЕВСКАЯ СОКРОВИЩНИЦА\n";
    std::cout << "=======================================================\n\n";
    std::cout << "    " << (pClass == "Рыцарь" ? "[===]" : " /\\ ") << "                            \n";
    std::cout << "    (o.o)                            ";
    if (!isOpen) {
        std::cout << " .--------.\n    / | \\                           / .----. \\\n    _/_\\_                          |==| [X] |==|\n                                    _\\______/_\n";
    } else {
        std::cout << " .--------.\n    / | \\                           /  ||||  \\\n    _/_\\_                          |==| [ ] |==|\n                                    _\\______/_\n\n\t\t* СУНДУК ОТКРЫТ! *\n";
    }
    std::cout << "\n=======================================================\n";
}

void Renderer::drawCrown() {
    std::cout << "       _  _  _ \n     / \\/ \\/ \\\n     \\_________/\n      ========= \n";
}

void Renderer::drawDragonScene(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP) {
    drawHealthBars(pName, pHP, pMaxHP, mName, mHP, mMaxHP);
    std::cout << "    " << (pClass == "Рыцарь" ? "[===]" : " /\\ ") << "                               ^__^        \n";
    std::cout << "    (o.o)                              /(_)(_)\\     \n";
    std::cout << "    / | \\                             /_ <==> _\\    \n";
    std::cout << "    _/_\\_                            /  \\____/  \\   \n";
    std::cout << "=======================================================\n";
}

void Renderer::drawDragonPlayerAttack(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP) {
    drawHealthBars(pName, pHP, pMaxHP, mName, mHP, mMaxHP);
    std::cout << "               " << (pClass == "Рыцарь" ? "[===]" : " /\\ ") << " ===> *БЕМС*            ^__^        \n";
    std::cout << "               (o.o)                    /(X)(X)\\     \n";
    std::cout << "               / | \\                  /_ <==> _\\    \n";
    std::cout << "               _/_\\_                 /  \\____/  \\   \n";
    std::cout << "=======================================================\n";
}

void Renderer::drawDragonMonsterAttack(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP) {
    drawHealthBars(pName, pHP, pMaxHP, mName, mHP, mMaxHP);
    std::cout << "    " << (pClass == "Рыцарь" ? "[===]" : " /\\ ") << "             *ОГОНЬ!*          ^__^        \n";
    std::cout << "    ( >_< )  <=========================/(_)(_)\\     \n";
    std::cout << "    / | \\                             /_ <==> _\\    \n";
    std::cout << "    _/_\\_                            /  \\____/  \\   \n";
    std::cout << "=======================================================\n";
}
