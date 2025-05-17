#include "domain/Item.h"
#include <gtest/gtest.h>

TEST(ItemTest, ToString) {
    Item item(1, "콜라", 1500, 10);
    EXPECT_EQ(item.toString(), "01) 콜라 : 1500");
}
