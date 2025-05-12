#pragma once
#include "Validator.h"
#include "ItemManager.h"

class LocalItemValidateAdapter : public Validator {
private:
    ItemManager& itemManager;
public:
    LocalItemValidateAdapter(ItemManager& manager);
    std::pair<std::string, bool> validate(const Payment& p) override;
};