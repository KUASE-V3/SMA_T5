#include "ItemManager.h"
#include "ItemFactory.h"
#include <algorithm>
#include <iostream>

ItemManager::ItemManager() {
    for (const auto &item : ItemFactory::createInitialItems()) {
        items.push_back(item);
    }
}

ItemManager &ItemManager::getInstance() {
    static ItemManager instance;
    return instance;
}

std::vector<Item> ItemManager::getItems() const {
    return items;
}

bool ItemManager::isValid(int itemcode, int quantity) const {
    auto it = std::find_if(items.begin(), items.end(),
                           [&itemcode](const Item &item) { return item.getCode() == itemcode; });

    if (it != items.end()) {
        return it->isValid(quantity);
    }
    return false;
}

bool ItemManager::increaseStock(const int itemCode, int quantity) {
    auto it = std::find_if(items.begin(), items.end(),
                           [&itemCode](Item &item) { return item.getCode() == itemCode; });

    if (it != items.end()) {
        return it->add(quantity);
    }
    return false;
}

bool ItemManager::decreaseStock(const int itemCode, int quantity) {
    auto it = std::find_if(items.begin(), items.end(),
                           [&itemCode](Item &item) { return item.getCode() == itemCode; });

    if (it != items.end()) {
        return it->consume(quantity);
    }
    return false;
}

std::string ItemManager::getName(int itemCode) const {
    auto it = std::find_if(items.begin(), items.end(),
                           [itemCode](const Item &item) { return item.getCode() == itemCode; });

    if (it != items.end()) {
        return it->getName();
    }

    return "";
}