#pragma once
#include <string>
#include <vector>
#include "Payment.h"

class Bank {
private:
    std::vector<std::string> cardInfoList;

public:
    Bank();  // 기본 카드 목록 초기화
    bool isValid(const std::string& cardNumber) const;
    bool pay(const Payment& payment);
};  