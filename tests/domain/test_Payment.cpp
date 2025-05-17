#include "CardPay.h"
#include "ItemManager.h"
#include "LocalItemValidateAdapter.h"
#include "Payment.h"
#include "RemoteItemValidateAdapter.h"
#include "ValidatorFactory.h"
#include <gtest/gtest.h>

TEST(PaymentBasicFieldsTest, ItemsAndPrepay) {
    auto method = std::make_unique<CardPay>("1234567812345678");
    Payment payment(42, 3, std::move(method));
    payment.setCertCode(101);

    auto [itemcode, quantity] = payment.getItems();
    EXPECT_EQ(itemcode, 42);
    EXPECT_EQ(quantity, 3);
    EXPECT_EQ(payment.getCertCode(), 101);
}

TEST(PaymentValidatorTest, CanLocalBuyTrue) {
    auto method = std::make_unique<CardPay>("1234567812345678");
    Payment payment(1, 3, std::move(method)); // 수량 3 요청 → 충분함

    EXPECT_TRUE(payment.canLocalBuy());
}

TEST(PaymentValidatorTest, CanLocalBuyFalseItemCode) {
    auto method = std::make_unique<CardPay>("1234567812345678");
    Payment payment(1000, 3, std::move(method)); // 없는 아이템템

    EXPECT_FALSE(payment.canLocalBuy());
}

TEST(PaymentValidatorTest, CanLocalBuyFalseCard) {
    auto method = std::make_unique<CardPay>("1"); // 카드 번호 다름
    Payment payment(1, 3, std::move(method));

    EXPECT_FALSE(payment.canLocalBuy());
}

TEST(PaymentValidatorTest, CanLocalBuyFalseItem) {

    auto method = std::make_unique<CardPay>("1111222233334444");
    Payment payment(1, 50, std::move(method)); // 수량 50 요청

    EXPECT_FALSE(payment.canLocalBuy());
}

TEST(PaymentValidatorTest, CanRemoteBuyTrue) {
    auto method = std::make_unique<CardPay>("1111222233334444");
    Payment payment(1, 1, std::move(method));

    EXPECT_TRUE(payment.canRemoteBuy());
}

TEST(PaymentValidatorTest, CanRemoteBuyFalseCard) {
    auto method = std::make_unique<CardPay>("1"); // 카드 번호 다름
    Payment payment(1, 3, std::move(method));

    EXPECT_FALSE(payment.canRemoteBuy());
}

TEST(PaymentBasicFieldsTest, BuyContentIsCorrectlyStored) {
    std::string cardNum = "1234567812345678";
    auto method = std::make_unique<CardPay>(cardNum);
    Payment payment(42, 3, std::move(method));

    const PaymentMethod *basePtr = payment.getbuyContent();
    ASSERT_NE(basePtr, nullptr); // buyContent가 null이 아니어야 함

    // CardPay*로 캐스팅
    auto *card = dynamic_cast<const CardPay *>(basePtr);
    ASSERT_NE(card, nullptr) << "buyContent가 CardPay가 아님";

    // 카드 번호가 잘 보존됐는지 확인
    EXPECT_EQ(card->getCardNumber(), cardNum);
}
