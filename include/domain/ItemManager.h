#pragma once
#include "Item.h"
#include "ItemValidator.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

class ItemManager : public ItemValidator {
  private:
    std::vector<Item> items;

    ItemManager();
    ItemManager(const ItemManager &) = delete;
    ItemManager &operator=(const ItemManager &) = delete;

  public:
    static ItemManager &getInstance();

    std::vector<Item> getItems() const;
    bool isValid(std::optional<int> itemcode, std::optional<int> quantity) const override;
    bool increaseStock(const int itemCode, int quantity);
    bool decreaseStock(const int itemCode, int quantity);
    std::string getName(int itemCode) const;
    bool isValidType(std::optional<int> itemcode, std::optional<int> quantity) const;
    // void add(const std::string &name, int price, int count);
    //  Item *findByName(const std::string &name);
};