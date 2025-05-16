#include "Payment.h"

void Payment::addItem(const std::string &name, int quantity)
{
    items.emplace_back(name, quantity);
}

void Payment::setCertCode(int code)
{
    certCode = code;
}

int Payment::getCertCode() const
{
    return certCode;
}