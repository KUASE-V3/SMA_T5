#pragma once
#include "PaymentMethod.h"
#include <string>

class CardPay : public PaymentMethod {
  private:
    std::string cardInfo;

  public:
    explicit CardPay(const std::string &cardNum);
    std::string getCardInfo() const;
    bool isValid() const override;
};