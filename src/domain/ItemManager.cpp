#include "ItemManager.h"
#include "ItemFactory.h"
#include <iostream>
#include <algorithm>

ItemManager::ItemManager(){
    for (const auto &item : ItemFactory::createInitialItems()) {
        items.push_back(item);
    }
}

ItemManager& ItemManager::getInstance(){
    static ItemManager instance;
    return instance;
}

std::vector<Item> ItemManager::getItems() const {
    return items;
}

bool ItemManager::isValid(const std::string& itemName, int quantity) const{
    auto it = std::find_if(items.begin(), items.end(), [&itemName](const Item& item){
        return item.getName() == itemName;
    });

    if (it != items.end()){
        return it -> isValid(quantity);
    }
    return false;
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