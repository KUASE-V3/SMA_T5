#include <gtest/gtest.h>
#include "Item.h"

TEST(ItemTest, GettersReturnCorrectValues) {
    Item item(1, "콜라", 1500, 10);
    EXPECT_EQ(item.getCode(), 1);
    EXPECT_EQ(item.getName(), "콜라");
    EXPECT_EQ(item.getPrice(), 1500);
}

TEST(ItemTest, IsValidChecksStockCorrectly) {
    Item item(1, "콜라", 1500, 5);
    EXPECT_TRUE(item.isValid(3));
    EXPECT_TRUE(item.isValid(5));
    EXPECT_FALSE(item.isValid(6));
}

TEST(ItemTest, AddIncreasesStock) {
    Item item(1, "콜라", 1500, 5);
    EXPECT_TRUE(item.add(3));
    EXPECT_FALSE(item.add(0));
    EXPECT_FALSE(item.add(-1));
}

TEST(ItemTest, BuyReducesStockCorrectly) {
    Item item(1, "콜라", 1500, 10);
    EXPECT_TRUE(item.buy(3));  // 성공
    EXPECT_FALSE(item.buy(20)); // 실패: 수량 초과
    EXPECT_FALSE(item.buy(0));  // 실패: 0개
    EXPECT_FALSE(item.buy(-5)); // 실패: 음수
}

TEST(ItemTest, ToStringFormatsCorrectly) {
    Item item(1, "콜라", 1500, 10);
    EXPECT_EQ(item.toString(), "01) 콜라 : 1500");
}
