#include "domain/CLManager.h"
#include <climits> // INT_MAX
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

TEST(CLManagerTest, ShowItemsPrintsCorrectly) {
    CLManager &clManager = CLManager::getInstance();

    // 출력 캡처
    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    clManager.showItems();

    std::cout.rdbuf(oldCout); // 복구

    std::string output = buffer.str();

    EXPECT_NE(output.find("콜라"), std::string::npos);
    EXPECT_NE(output.find("카페라떼"), std::string::npos);
    EXPECT_NE(output.find("1500"), std::string::npos);
    EXPECT_NE(output.find("2200"), std::string::npos);
}

TEST(CLManagerTest, OrderReturnsAnyValidStatus) {
    CLManager &manager = CLManager::getInstance();

    int itemCode = 1; // 예: 콜라
    int quantity = 1;
    std::string card = "12345678123456789";

    ORDER_STATUS status = manager.order(itemCode, quantity, card);

    EXPECT_TRUE(status == ORDER_STATUS::LOCAL || status == ORDER_STATUS::REMOTE ||
                status == ORDER_STATUS::FAIL);
}