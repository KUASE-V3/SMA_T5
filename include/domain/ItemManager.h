#pragma once
#include "Item.h"
#include "ItemValidator.h"
#include <string>
#include <unordered_map>
#include <vector>

class ItemManager : public ItemValidator{
  private:
    std::vector<Item> items;
    ItemManager();
  public:
    ItemManager(const ItemManager&) = delete;
    ItemManager& operator = (const ItemManager&) = delete;

    static ItemManager& getInstance();
    
    std::vector<Item> getItems() const;
    bool isValid(const std::string& itemName, int quantity) const;
    // void add(const std::string &name, int price, int count);
    // Item *findByName(const std::string &name);
    // bool modifyStock(ModifyType type, const std::string& itemName, int quantity);
};