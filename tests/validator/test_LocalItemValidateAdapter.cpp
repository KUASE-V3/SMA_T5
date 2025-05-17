#include <gtest/gtest.h>
#include "Payment.h"
#include "LocalItemValidateAdapter.h"
#include "ItemManager.h"

TEST(LocalItemValidateAdapterTest, ValidItemReturnsTrue) {
    auto& manager = ItemManager::getInstance();

    Payment payment(1, 4, nullptr);  // 결제 아이템: 1 4개
    LocalItemValidateAdapter adapter;

    EXPECT_TRUE(adapter.validate(payment));
}

TEST(LocalItemValidateAdapterTest, NotEnoughStockReturnsFalse) {
    auto& manager = ItemManager::getInstance();

    Payment payment(1, 11, nullptr);  // 11개 요청(재고 없음)
    LocalItemValidateAdapter adapter;

    EXPECT_FALSE(adapter.validate(payment));
}

TEST(LocalItemValidateAdapterTest, ItemNotFoundReturnsFalse) {
    auto& manager = ItemManager::getInstance();

    Payment payment(21, 1, nullptr); //음료 없음
    LocalItemValidateAdapter adapter;

    EXPECT_FALSE(adapter.validate(payment));
}
