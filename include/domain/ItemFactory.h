#pragma once
#include "Item.h"
#include <vector>

class ItemFactory {
  public:
    static std::vector<Item> createInitialItems();
};