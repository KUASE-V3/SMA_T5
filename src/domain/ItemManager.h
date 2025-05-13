#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Item.h"

class ItemManager {
private:
    std::unordered_map<std::string, Item> items;

public:
    void addItem(const std::string& name, int price, int count);
    Item* findByName(const std::string& name);
    std::vector<std::string> getNames();

    // 추가 기능
    bool buyItem(const std::string& name, int quantity);
    bool addStock(const std::string& name, int quantity);
    void printInventory() const;
};