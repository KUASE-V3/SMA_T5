#pragma once
#include <string>

class ItemValidator{
    public:
    virtual ~ItemValidator() = default;

    virtual bool isValid(const std::string& itemName, int quantity) const = 0;
};