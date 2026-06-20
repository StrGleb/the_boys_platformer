#pragma once
#include <string>

class Renderer {
public:
    static void clearScreen();
    static void sleep(int milliseconds);
    static void drawHealthBars(const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP);
    static void drawBattleScene(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP);
    static void drawPlayerAttackScene(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP);
    static void drawMonsterAttackScene(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP);
    static void drawChestScene(const std::string& pClass, bool isOpen);
    static void drawCrown();
    static void drawDragonScene(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP);
    static void drawDragonPlayerAttack(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP);
    static void drawDragonMonsterAttack(const std::string& pClass, const std::string& pName, int pHP, int pMaxHP, const std::string& mName, int mHP, int mMaxHP);
};
