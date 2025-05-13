#include "CLManager.h"
#include <iostream>

void CLManager::showItems() {
    auto names = itemManager.getNames();
    std::cout << "Available Items:\n";
    for (const auto& name : names) {
        std::cout << "- " << name << '\n';
    }
}

void CLManager::buy(const std::string& itemName, int quantity) {
    Item* item = itemManager.findByName(itemName);
    if (!item) {
        std::cout << "Item not found.\n";
        return;
    }
    if (!item->isValid(quantity)) {
        std::cout << "Insufficient stock.\n";
        return;
    }
    item->buy(quantity);
    std::cout << "Purchase successful: " << itemName << " x" << quantity << '\n';
}

void CLManager::prePay(Payment& payment) {
    int code = 1000 + rand() % 9000; // 예시용 난수 코드
    payment.setPrepayCode(code);
    std::cout << "Prepay Code: " << code << '\n';
}