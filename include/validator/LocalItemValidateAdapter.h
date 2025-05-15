#pragma once
#include "ItemValidator.h"
#include "ItemManager.h"
#include "LocalValidator.h"
#include "Payment.h"

class LocalItemValidateAdapter : public LocalValidator {
  private:
    ItemValidator* itemManager = &ItemManager::getInstance();

  public:
    // LocalItemValidateAdapter(ItemManager& manager);
    bool validate(const Payment& p) const override;
};