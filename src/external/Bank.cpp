#include "Bank.h"
#include <iostream>

Bank::Bank() {
    // 예시용 유효 카드 번호 추가
    cardInfoList.push_back("1234-5678-9012-3456");
    cardInfoList.push_back("9876-5432-1098-7654");
}

bool Bank::isValid(const std::string& cardNumber) const {
    for (const auto& card : cardInfoList) {
        if (card == cardNumber) return true;
    }
    return false;
}

bool Bank::pay(const Payment& payment) {
    // 예시: 카드 번호가 "1234-5678-9012-3456"일 때만 결제 성공 처리
    std::string dummyCard = "1234-5678-9012-3456";  // 실제 구현에서는 PaymentMethod에서 받아야 함

    if (!isValid(dummyCard)) {
        std::cout << "Card is not valid.\n";
        return false;
    }

    std::cout << "Payment successful!\n";
    return true;
}