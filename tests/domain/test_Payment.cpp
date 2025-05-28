#include "CardPay.h"
#include "ItemManager.h"
#include "LocalItemValidateAdapter.h"
#include "Payment.h"
#include "RemoteItemValidateAdapter.h"
#include "ValidatorFactory.h"
#include <optional>
#include <gtest/gtest.h>

TEST(PaymentBasicFieldsTest, ItemsAndPrepay) {
    auto method = std::make_unique<CardPay>("1234567812345678");
    Payment payment(42, 3, std::move(method));
    payment.setCertCode("5AAAA");

    auto itemcode = payment.getItemCode();
    auto quantity = payment.getQuantity();
    EXPECT_EQ(itemcode, 42);
    EXPECT_EQ(quantity, 3);
    EXPECT_EQ(payment.getCertCode(), "5AAAA");
}

TEST(PaymentValidatorTest, CanLocalBuyTrue) {
    ItemManager &manager = ItemManager::getInstance();
    manager.increaseStock(1, 3); // 재고 3개 이상 확보
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

    ItemManager &manager = ItemManager::getInstance();

    while (manager.decreaseStock(1, 50)) {
    } // 재고 50개 이하로
    Payment payment(1, 50, std::move(method)); // 수량 50 요청

    EXPECT_FALSE(payment.canLocalBuy());
}

// TODO
// TEST(PaymentValidatorTest, CanRemoteBuyTrue) {
//     auto method = std::make_unique<CardPay>("1111222233334444");
//     Payment payment(1, 1, std::move(method));

//     EXPECT_TRUE(payment.canRemoteBuy());
// }

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
    EXPECT_EQ(card->getCardInfo(), cardNum);
}

TEST(PaymentTest, PaySuccess) {
    // 유효한 카드 번호 (Bank 클래스 내부 목록과 일치해야 함)
    std::string validCard = "1234567812345678";
    std::unique_ptr<PaymentMethod> method = std::make_unique<CardPay>(validCard);
    Payment payment(1, 1, std::move(method));

    bool result = payment.pay();

    EXPECT_TRUE(result);
}

TEST(PaymentTest, PayFailsWhenCardHasNoBalance) {
    // 유효한 카드 번호 (Bank 클래스 내부 목록과 일치해야 함)
    std::string validCard = "0000000000000000";
    std::unique_ptr<PaymentMethod> method = std::make_unique<CardPay>(validCard);
    Payment payment(1, 1, std::move(method));

    bool result = payment.pay();

    EXPECT_FALSE(result);
}

TEST(PaymentTest, PayFailsWhenCardIsNotRegistered) {
    // 존재하지 않는 카드 번호
    std::string invalidCard = "1111111111111111";
    std::unique_ptr<PaymentMethod> method = std::make_unique<CardPay>(invalidCard);
    Payment payment(1, 1, std::move(method));

    bool result = payment.pay();

    EXPECT_FALSE(result);
}


TEST(PaymentTest, isNotValidPaymentWithNoneQuantity){
    // 아이템 개수 없고 코드 맞을 떄

    Payment payment(1);
    bool result = payment.validate();

    EXPECT_TRUE(result);
}

TEST(PaymentTest, isNotValidPaymentWithERRORCode){

    Payment payment(0);
    bool result = payment.validate();

    EXPECT_FALSE(result);
}

TEST(PaymentTest, isNotValidPaymentWithERRORQuantity){

    Payment payment(1, 1000);
    bool result = payment.validate();

    EXPECT_FALSE(result);
}