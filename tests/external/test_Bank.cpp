#include "domain/CardPay.h"
#include "domain/Payment.h"
#include "external/Bank.h"
#include <gtest/gtest.h>

TEST(BankTest, PaySuccess) {
    std::unique_ptr<PaymentMethod> method = std::make_unique<CardPay>("1234567812345678");
    Payment payment(1, 1, std::move(method)); // itemCode 1, quantity 1

    bool result = Bank::getInstance().pay(payment);

    EXPECT_TRUE(result);
}

TEST(BankTest, PayFailsWhenMethodIsNotRegistered) {
    std::unique_ptr<PaymentMethod> method = std::make_unique<CardPay>("9999999999999999");
    Payment payment(1, 1, std::move(method));

    bool result = Bank::getInstance().pay(payment);

    EXPECT_FALSE(result);
}

TEST(BankTest, PayFailsWhenMethodHasNoBalance) {
    std::unique_ptr<PaymentMethod> method = std::make_unique<CardPay>("0000000000000000");
    Payment payment(1, 1, std::move(method));

    bool result = Bank::getInstance().pay(payment);

    EXPECT_FALSE(result);
}