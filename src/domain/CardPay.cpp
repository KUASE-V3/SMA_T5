#include "CardPay.h"

CardPay::CardPay(const std::string &cardNum) : cardInfo(cardNum) {}

std::string CardPay::getCardInfo() const {
    return cardInfo;
}

bool CardPay::isValid() const {
    return !cardInfo.empty() && cardInfo.length() >= 16;
}