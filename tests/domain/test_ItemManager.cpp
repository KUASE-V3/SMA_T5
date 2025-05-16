#include "domain/ItemManager.h"
#include <gtest/gtest.h>

TEST(ItemManagerTest, ItemsAreInitializedCorrectly) {
    ItemManager manager;
    const auto &items = manager.getItems();

    EXPECT_EQ(items.size(), 20); // 총 20개 항목

    EXPECT_EQ(items[0].getName(), "콜라");
    EXPECT_EQ(items[0].getPrice(), 1500);
    EXPECT_EQ(items[19].getName(), "카페라떼");
    EXPECT_EQ(items[19].getPrice(), 2200);
}