#include "Bank.h"
#include "CardPay.h"
#include "Payment.h"
#include <iostream>

Bank::Bank() {
    // 유효 카드 번호 추가
    cardBalanceMap["1234567812345678"] = 1000000000;
    cardBalanceMap["0000000000000000"] = 0;
    cardBalanceMap["[][][][][][][][]"] = 1000000000;
    cardBalanceMap["123-123-123-1234"] = 1000000000;
}

Bank &Bank::getInstance() {
    static Bank instance;
    return instance;
}

bool Bank::isValid(const std::string &cardInfo) const {
    return cardBalanceMap.find(cardInfo) != cardBalanceMap.end();
}

bool Bank::hasEnoughBalance(const std::string &cardInfo, int amount) const {
    auto it = cardBalanceMap.find(cardInfo);
    return it != cardBalanceMap.end() && it->second >= amount;
}

bool Bank::pay(const Payment &payment) {
    const PaymentMethod *method = payment.getbuyContent();
    const CardPay *cardPay = dynamic_cast<const CardPay *>(method);

    if (cardPay) {
        std::string card = cardPay->getCardInfo();
        int amount = payment.getTotalPrice();

        if (!isValid(card)) {
            return false;
        }

        if (!hasEnoughBalance(card, amount)) {
            return false;
        }

        cardBalanceMap[card] -= amount;
        return true;
    }

    return false;
}