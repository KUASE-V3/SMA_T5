#include "ItemManager.h"
#include <iostream>

void ItemManager::addItem(const std::string& name, int price, int count) {
    items.emplace(name, Item(name, price, count));
}

Item* ItemManager::findByName(const std::string& name) {
    auto it = items.find(name);
    if (it != items.end()) return &it->second;
    return nullptr;
}

std::vector<std::string> ItemManager::getNames() {
    std::vector<std::string> names;
    for (const auto& pair : items) {
        names.push_back(pair.first);
    }
    return names;
}

// 추가 기능들
bool ItemManager::buyItem(const std::string& name, int quantity) {
    Item* item = findByName(name);
    if (!item) return false;
    return item->buy(quantity);
}

bool ItemManager::addStock(const std::string& name, int quantity) {
    Item* item = findByName(name);
    if (!item) return false;
    return item->add(quantity);
}

void ItemManager::printInventory() const {
    std::cout << "Current Inventory:\n";
    for (const auto& [name, item] : items) {
        std::cout << "- " << name << " | Price: " << item.getPrice() << '\n';
    }
}