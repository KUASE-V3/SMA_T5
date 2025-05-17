#include <gtest/gtest.h>
#include "ItemManager.h"
#include "Item.h"

TEST(ItemManagerTest, GetItemsReturnsCorrectData) {

    auto items = ItemManager::getInstance().getItems();
    ASSERT_EQ(items.size(), 20);
    EXPECT_EQ(items[0].getName(), "콜라");
    EXPECT_EQ(items[0].getCode(), 1);
}

TEST(ItemManagerTest, IsValidReturnsTrueWhenStockSuffices) {

    EXPECT_TRUE(ItemManager::getInstance().isValid(1, 5));
}

TEST(ItemManagerTest, IsValidReturnsFalseWhenStockInsufficient) {
    EXPECT_FALSE(ItemManager::getInstance().isValid(1, 20));
}

TEST(ItemManagerTest, IsValidReturnsFalseWhenItemNotFound) {
    EXPECT_FALSE(ItemManager::getInstance().isValid(999, 1));
}