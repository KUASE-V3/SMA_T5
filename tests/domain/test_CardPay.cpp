#include <gtest/gtest.h>
#include "CardPay.h"


TEST(CardPayTest, IsValidCardNum){
    auto card = CardPay("1234567812345678");

    EXPECT_TRUE(card.isValid());
}


TEST(CardPayTest, IsUnValidCardNumNone){
    auto card = CardPay("");

    EXPECT_FALSE(card.isValid());
}
TEST(CardPayTest, IsUnValidCardNum){
    auto card = CardPay("123");

    EXPECT_FALSE(card.isValid());
}
