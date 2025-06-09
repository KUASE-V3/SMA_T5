#include <gtest/gtest.h>
#include "CardPay.h"


TEST(CardPayTest, IsValidCardNum){
    CardPay card = CardPay("1234567812345678");

    EXPECT_TRUE(card.isValid());
}


TEST(CardPayTest, IsUnValidCardNumNone){
    CardPay card = CardPay("");

    EXPECT_FALSE(card.isValid());
}
TEST(CardPayTest, IsUnValidCardNum){
    CardPay card = CardPay("123");

    EXPECT_FALSE(card.isValid());
}
