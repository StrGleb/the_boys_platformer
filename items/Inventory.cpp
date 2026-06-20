#include "Inventory.h"
#include <iostream>

Inventory::Inventory() : maxSlots(5) {}

bool Inventory::addItem(const Item& item) {
    if (slots.size() < maxSlots) {
        slots.push_back(item);
        std::cout << "Предмет " << item.getName() << " добавлен в инвентарь.\n";
        return true;
    }
    std::cout << "Инвентарь полон!\n";
    return false;
}

void Inventory::removeItem(size_t index) {
    if (index < slots.size()) slots.erase(slots.begin() + index);
}

void Inventory::printInventory() const {
    for (size_t i = 0; i < slots.size(); ++i) {
        std::cout << i + 1 << ". " << slots[i].getName() << "\n";
    }
}

bool Inventory::isEmpty() const { return slots.empty(); }
size_t Inventory::getSize() const { return slots.size(); }
Item Inventory::getItem(size_t index) const { return slots[index]; }
