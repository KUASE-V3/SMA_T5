#pragma once
#include "Item.h"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class ItemFactory {
  public:
   static json itemList;
   static std::vector<Item> createInitialItems();
};