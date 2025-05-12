#include "Payment.h"

void Payment::addItem(const std::string& name, int quantity) {
    items.emplace_back(name, quantity);
}

std::vector<std::pair<std::string, int>> Payment::getItems() const {
    return items;
}

void Payment::setPrepayCode(int code) {
    prepayCode = code;
}

int Payment::getPrepayCode() const {
    return prepayCode;
}