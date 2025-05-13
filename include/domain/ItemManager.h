#pragma once
#include "Item.h"
#include <string>
#include <unordered_map>
#include <vector>

class ItemManager {
  private:
    std::vector<Item> items;

  public:
    ItemManager();
    std::vector<Item> getItems() const;

    // void add(const std::string &name, int price, int count);
    // Item *findByName(const std::string &name);
    // bool modifyStock(ModifyType type, const std::string& itemName, int quantity);
};