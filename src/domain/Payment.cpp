#include "Payment.h"

void Payment::addItem(const std::string &name, int quantity)
{
    items.emplace_back(name, quantity);
}

void Payment::setPrepayCode(int code)
{
    prepayCode = code;
}

int Payment::getPrepayCode() const
{
    return prepayCode;
}