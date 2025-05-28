#pragma once
#include "Validator.h"
#include "ItemManager.h"
#include "Payment.h"

class ItemTypeValidateAdapter : public Validator {
    private:
    ItemManager& Itemmanager = ItemManager::getInstance();
    public:
    bool validate(const Payment& p) const override;
};