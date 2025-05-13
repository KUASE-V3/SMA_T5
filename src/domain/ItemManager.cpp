#include "ItemManager.h"
#include "ItemFactory.h"
#include <iostream>

ItemManager::ItemManager() {
    for (const auto &item : ItemFactory::createInitialItems()) {
        items.push_back(item);
    }
}

std::vector<Item> ItemManager::getItems() const {
    return items;
}

// void ItemManager::add(const std::string &name, int price, int count) {
//     int id = items.size() + 1;
//     items.emplace_back(id, name, price, count);
// }

// Item *ItemManager::findByName(const std::string &name) {
//     return nullptr;
// }

// bool modifyStock(ModifyType type, const std::string &itemName, int quantity)
// {
// }