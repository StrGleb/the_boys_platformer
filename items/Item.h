#pragma once
#include <string>

class Item {
private:
    std::string name;
    std::string type; 
    int value;

public:
    Item();
    Item(std::string n, std::string t, int v);
    std::string getName() const;
    std::string getType() const;
    int getValue() const;
};
