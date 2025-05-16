#pragma once
#include <string>

class ItemValidator{
    public:
    virtual ~ItemValidator() = default;

    virtual bool isValid(int itemcode, int quantity) const = 0;
};