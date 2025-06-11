#include "ItemFactory.h"
#include "domain/CLManager.h"
#include "domain/CardPay.h"
#include <climits> // INT_MAX
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

using namespace std;

class CLManagerTest : public ::testing::Test {
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

TEST_F(CLManagerTest, ShowItemsPrintsCorrectly) {
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
    EXPECT_NE(output.find("1200"), std::string::npos);
}

// Local 조건 테스트
TEST_F(CLManagerTest, OrderReturnsLocalWhenCanLocalBuyIsTrue) {
    CLManager &manager = CLManager::getInstance();

    int itemCode = 1;
    int quantity = 1;
    std::string validCard = "1234567812345678"; // Bank에 등록된 카드, 잔액 충분
    ItemManager::getInstance().increaseStock(itemCode, quantity);

    auto method = std::make_unique<CardPay>(validCard);
    auto payment = std::make_unique<Payment>(itemCode, quantity, std::move(method));
    ORDER_STATUS status = manager.order(payment);

    EXPECT_EQ(status, ORDER_STATUS::LOCAL);
    EXPECT_NE(payment, nullptr); // payment 객체는 생성되어야 함
}

// FAIL 조건 테스트
TEST_F(CLManagerTest, OrderReturnsFailWhenNeitherLocalNorRemoteValid) {
    CLManager &manager = CLManager::getInstance();

    std::string invalidCard = "0000000000000000";
    int itemCode = 1;         // 정상 아이템 코드
    int quantity = 999999999; // 어디서도 구매 불가한 재고

    auto method = std::make_unique<CardPay>(invalidCard);
    auto payment = std::make_unique<Payment>(itemCode, quantity, std::move(method));
    ORDER_STATUS status = manager.order(payment);

    EXPECT_EQ(status, ORDER_STATUS::FAIL);
}

TEST_F(CLManagerTest, PayTrueWhenPaymentSucceess) {
    // Bank에 충분한 잔고가 있는 카드
    std::string validCard = "1234567812345678";
    auto method = std::make_unique<CardPay>(validCard);
    auto payment = std::make_unique<Payment>(1, 1, std::move(method));

    CLManager &manager = CLManager::getInstance();
    bool result = manager.pay(payment);

    EXPECT_TRUE(result);
}

TEST_F(CLManagerTest, PayReturnsFalseWhenCardHasNoBalance) {
    // Bank에 등록되지 않은 카드
    std::string invalidCard = "0000000000000000"; // 잔액 없는 카드
    auto method = std::make_unique<CardPay>(invalidCard);
    auto payment = std::make_unique<Payment>(1, 1, std::move(method));

    CLManager &manager = CLManager::getInstance();
    bool result = manager.pay(payment);

    EXPECT_FALSE(result);
}

TEST_F(CLManagerTest, PayReturnsFalseWhenInvalidCard) {
    // Bank에 등록되지 않은 카드
    std::string invalidCard = "9999999999999999";
    auto method = std::make_unique<CardPay>(invalidCard);
    auto payment = std::make_unique<Payment>(1, 1, std::move(method));

    CLManager &manager = CLManager::getInstance();
    bool result = manager.pay(payment);

    EXPECT_FALSE(result);
}