#pragma once
#include <string>
#include <optional>

class ItemValidator{
    public:
    virtual ~ItemValidator() = default;

    virtual bool isValid(std::optional<int> itemcode, std::optional<int> quantity) const = 0;
};