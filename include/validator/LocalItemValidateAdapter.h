#pragma once
#include "ItemValidator.h"
#include "ItemManager.h"
#include "Validator.h"
#include "Payment.h"

class LocalItemValidateAdapter : public Validator {
  private:
    ItemValidator* itemManager = &ItemManager::getInstance();

  public:
    // LocalItemValidateAdapter(ItemManager& manager);
    bool validate(const Payment& p) const override;
};