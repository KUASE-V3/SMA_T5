#include "CLManager.h"
#include <iostream>

void CLManager::showItems() {
    auto items = itemManager.getItems();
    for (const auto &item : items) {
        std::cout << item.toString() << '\n';
    }
}