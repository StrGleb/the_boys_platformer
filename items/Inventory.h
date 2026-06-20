#pragma once
#include <vector>
#include "Item.h"

class Inventory {
private:
    std::vector<Item> slots;
    size_t maxSlots;

public:
    Inventory();
    bool addItem(const Item& item);
    void removeItem(size_t index);
    void printInventory() const;
    bool isEmpty() const;
    size_t getSize() const;
    Item getItem(size_t index) const;
};
