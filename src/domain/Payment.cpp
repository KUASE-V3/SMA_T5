#include "Payment.h"

void Payment::addItem(const std::string &name, int quantity)
{
    items.first = name;
    items.second = quantity;
}

void Payment::setPrepayCode(int code)
{
    prepayCode = code;
}

int Payment::getPrepayCode() const
{
    return prepayCode;
}

std::pair<std::string, int> Payment::getItems() const{
    return items;
}