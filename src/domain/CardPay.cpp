#include "CardPay.h"

CardPay::CardPay(const std::string& cardNum) : cardNumber(cardNum) {}

std::string CardPay::getCardNumber() const {
    return cardNumber;
}

bool CardPay::isValid() const {
    // 단순한 예시: 길이가 충분한지만 체크
    return !cardNumber.empty() && cardNumber.length() >= 16;
}