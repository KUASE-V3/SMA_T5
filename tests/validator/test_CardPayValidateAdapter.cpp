#include <gtest/gtest.h>
#include "CardPayValidateAdapter.h"
#include "CardPay.h"
#include "Payment.h"

TEST(CardPayValidateAdapterTest, ValidCardReturnsTrue) {
    auto method = std::make_unique<CardPay>("1234567812345678");
    Payment payment(1, 1, std::move(method));
    CardPayValidateAdapter adapter;

    EXPECT_TRUE(adapter.validate(payment));
}

TEST(CardPayValidateAdapterTest, InvalidCardReturnsFalse) {
    auto method = std::make_unique<CardPay>("12");  // 너무 짧음
    Payment payment(1, 1, std::move(method));
    CardPayValidateAdapter adapter;

    EXPECT_FALSE(adapter.validate(payment));
}

TEST(CardPayValidateAdapterTest, EmptyCardNumberIsInvalid) {
    auto method = std::make_unique<CardPay>("");  // 없음
    Payment payment(1, 1, std::move(method));
    CardPayValidateAdapter adapter;

    EXPECT_FALSE(adapter.validate(payment));
}


TEST(CardPayValidateAdapterTest, NotCardPayReturnsTrue) {
    class DummyMethod : public PaymentMethod {
        bool isValid() const override { return false; }
    };

    auto method = std::make_unique<DummyMethod>();
    Payment payment(1, 1, std::move(method));
    CardPayValidateAdapter adapter;

    // CardPay가 아니라면 adapter는 검사 건너뛰므로 true 반환
    EXPECT_TRUE(adapter.validate(payment));
}
