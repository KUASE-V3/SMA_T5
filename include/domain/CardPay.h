#pragma once
#include "PaymentMethod.h"
#include <string>

class CardPay : public PaymentMethod {
  private:
    std::string cardNumber;

  public:
    CardPay(const std::string &cardNum);
    std::string getCardNumber() const;
    bool isValid() const override; // 단순 형식 검사 or 존재 확인
};