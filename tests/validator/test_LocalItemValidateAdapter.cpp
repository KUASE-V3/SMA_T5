#include "ItemManager.h"
#include "LocalItemValidateAdapter.h"
#include "Payment.h"
#include <gtest/gtest.h>

TEST(LocalItemValidateAdapterTest, ValidItemReturnsTrue) {
    auto &manager = ItemManager::getInstance();

    manager.increaseStock(1, 4);    // 재고 4개 이상으로 만들기
    Payment payment(1, 4, nullptr); // 결제 아이템: 1 4개
    LocalItemValidateAdapter adapter;

    EXPECT_TRUE(adapter.validate(payment));
}

TEST(LocalItemValidateAdapterTest, NotEnoughStockReturnsFalse) {
    auto &manager = ItemManager::getInstance();

    while (manager.decreaseStock(1, 4)) {
        // 재고 4개 이하로 만들기
    }
    Payment payment(1, 4, nullptr); // 4개 요청(재고 없음)
    LocalItemValidateAdapter adapter;

    EXPECT_FALSE(adapter.validate(payment));
}

TEST(LocalItemValidateAdapterTest, ItemNotFoundReturnsFalse) {

    Payment payment(21, 1, nullptr); // 음료 없음
    LocalItemValidateAdapter adapter;

    EXPECT_FALSE(adapter.validate(payment));
}
