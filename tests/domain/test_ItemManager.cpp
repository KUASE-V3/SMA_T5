#include "Item.h"
#include "ItemManager.h"
#include <gtest/gtest.h>
#include <fstream>
#include "json.hpp"
#include "ItemFactory.h"

using json = nlohmann::json;

using namespace std;

class ItemManagerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    ifstream file("T5.json", std::ios::in);

    json j;

    if (!file.is_open()) {
      std::cerr << "Error opening file.\n";
      return;
    }
    file >> j;
    ItemFactory::itemList = j;
  }
};

TEST_F(ItemManagerTest, GetItemsReturnsCorrectData) {

    auto items = ItemManager::getInstance().getItems();

    ASSERT_EQ(items.size(), 20);
    EXPECT_EQ(items[0].getName(), "콜라");
    EXPECT_EQ(items[0].getCode(), 1);
}

TEST_F(ItemManagerTest, IsValidReturnsTrueWhenStockSuffices) {

    EXPECT_TRUE(ItemManager::getInstance().isValid(1, 5));
}

TEST_F(ItemManagerTest, IsValidReturnsFalseWhenStockInsufficient) {
    EXPECT_FALSE(ItemManager::getInstance().isValid(1, 20));
}

TEST_F(ItemManagerTest, IsValidReturnsFalseWhenItemNotFound) {
    EXPECT_FALSE(ItemManager::getInstance().isValid(999, 1));
}

TEST_F(ItemManagerTest, IncreaseStockSuccess) {
    ItemManager &manager = ItemManager::getInstance();

    // 기존 아이템 리스트에서 itemCode == 1을 찾음
    int itemCode = 1;
    const auto &items = manager.getItems();
    auto it = std::find_if(items.begin(), items.end(),
                           [itemCode](const Item &item) { return item.getCode() == itemCode; });

    ASSERT_NE(it, items.end()); // 아이템 존재 확인

    int before = it->getCount();

    // 증가
    bool result = manager.increaseStock(itemCode, 5);
    EXPECT_TRUE(result);

    // 업데이트된 재고 확인
    const auto &updatedItems = manager.getItems();
    auto updatedIt =
        std::find_if(updatedItems.begin(), updatedItems.end(),
                     [itemCode](const Item &item) { return item.getCode() == itemCode; });

    ASSERT_NE(updatedIt, updatedItems.end());
    EXPECT_EQ(updatedIt->getCount(), before + 5);
}
TEST_F(ItemManagerTest, DecreaseStockSuccess) {
    ItemManager &manager = ItemManager::getInstance();
    int itemCode = 1;
    manager.increaseStock(itemCode, 10); // 충분한 재고 확보

    const auto &items = manager.getItems();
    auto it = std::find_if(items.begin(), items.end(),
                           [itemCode](const Item &item) { return item.getCode() == itemCode; });
    ASSERT_NE(it, items.end());

    int before = it->getCount();
    bool result = manager.decreaseStock(itemCode, 3);
    EXPECT_TRUE(result);

    const auto &updatedItems = manager.getItems();
    auto updatedIt =
        std::find_if(updatedItems.begin(), updatedItems.end(),
                     [itemCode](const Item &item) { return item.getCode() == itemCode; });
    ASSERT_NE(updatedIt, updatedItems.end());
    EXPECT_EQ(updatedIt->getCount(), before - 3);
}

TEST_F(ItemManagerTest, DecreaseStockFail_InsufficientStock) {
    ItemManager &manager = ItemManager::getInstance();
    int itemCode = 1;

    while (manager.decreaseStock(itemCode, 10)) {
        // 재고를 10개 이하로
    }

    const auto &items = manager.getItems();
    auto it = std::find_if(items.begin(), items.end(),
                           [itemCode](const Item &item) { return item.getCode() == itemCode; });
    ASSERT_NE(it, items.end());

    int before = it->getCount();
    bool result = manager.decreaseStock(itemCode, 10); // 초과 요청
    EXPECT_FALSE(result);

    const auto &updatedItems = manager.getItems();
    auto updatedIt =
        std::find_if(updatedItems.begin(), updatedItems.end(),
                     [itemCode](const Item &item) { return item.getCode() == itemCode; });
    ASSERT_NE(updatedIt, updatedItems.end());
    EXPECT_EQ(updatedIt->getCount(), before); // 수량 그대로여야 함
}

TEST_F(ItemManagerTest, InvalidItemCodeReturnsFalse) {
    ItemManager &manager = ItemManager::getInstance();
    int invalidCode = 9999;

    bool result1 = manager.increaseStock(invalidCode, 5);
    bool result2 = manager.decreaseStock(invalidCode, 3);

    EXPECT_FALSE(result1);
    EXPECT_FALSE(result2);
}