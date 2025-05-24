#include "domain/CLManager.h"
#include "domain/CardPay.h"
#include "ItemFactory.h"
#include <climits> // INT_MAX
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
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

// TEST(CLManagerTest, OrderReturnsAnyValidStatus) {
//     CLManager &manager = CLManager::getInstance();

//     int itemCode = 1; // 예: 콜라
//     int quantity = 1;
//     std::string card = "12345678123456789";
//     std::unique_ptr<Payment> payment;

//     ORDER_STATUS status = manager.order(itemCode, quantity, card, payment);

//     EXPECT_TRUE(status == ORDER_STATUS::LOCAL || status == ORDER_STATUS::REMOTE ||
//                 status == ORDER_STATUS::FAIL);
// }

// Local 조건 테스트
TEST_F(CLManagerTest, OrderReturnsLocalWhenCanLocalBuyIsTrue) {
    CLManager &manager = CLManager::getInstance();

    int itemCode = 1;
    int quantity = 1;
    std::string validCard = "1234567812345678"; // Bank에 등록된 카드, 잔액 충분
    ItemManager::getInstance().increaseStock(itemCode, quantity);

    std::unique_ptr<Payment> payment;
    ORDER_STATUS status = manager.order(itemCode, quantity, validCard, payment);

    EXPECT_EQ(status, ORDER_STATUS::LOCAL);
    EXPECT_NE(payment, nullptr); // payment 객체는 생성되어야 함
}

// // REMOTE 조건 테스트
// TEST(CLManagerTest, OrderReturnsRemoteWhenRemoteConditionMet) {
//     CLManager& manager = CLManager::getInstance();

//     // 원격 조건을 만족하는 유효한 카드번호 (예: 1234567812345678 → 잔액 충분, 재고 부족)
//     std::string validCard = "1234567812345678";
//     int itemCode = 20;  // 없는 아이템 코드로 재고 체크 실패 유도
//     int quantity = 1;

//     std::unique_ptr<Payment> payment;
//     ORDER_STATUS status = manager.order(itemCode, quantity, validCard, payment);

//     EXPECT_EQ(status, ORDER_STATUS::REMOTE);
// }

// FAIL 조건 테스트
TEST_F(CLManagerTest, OrderReturnsFailWhenNeitherLocalNorRemoteValid) {
    CLManager &manager = CLManager::getInstance();

    std::string invalidCard = "0000000000000000";
    int itemCode = 1;         // 정상 아이템 코드
    int quantity = 999999999; // 어디서도 구매 불가한 재고

    std::unique_ptr<Payment> payment;
    ORDER_STATUS status = manager.order(itemCode, quantity, invalidCard, payment);

    EXPECT_EQ(status, ORDER_STATUS::FAIL);
}

TEST_F(CLManagerTest, PayTrueWhenPaymentSucceess) {
    // Bank에 충분한 잔고가 있는 카드
    std::string validCard = "1234567812345678";
    auto method = std::make_unique<CardPay>(validCard);
    std::unique_ptr<Payment> payment = std::make_unique<Payment>(1, 1, std::move(method));

    CLManager &manager = CLManager::getInstance();
    bool result = manager.pay(payment);

    EXPECT_TRUE(result);
}

TEST_F(CLManagerTest, PayReturnsFalseWhenCardHasNoBalance) {
    // Bank에 등록되지 않은 카드
    std::string invalidCard = "0000000000000000"; // 잔액 없는 카드
    auto method = std::make_unique<CardPay>(invalidCard);
    std::unique_ptr<Payment> payment = std::make_unique<Payment>(1, 1, std::move(method));

    CLManager &manager = CLManager::getInstance();
    bool result = manager.pay(payment);

    EXPECT_FALSE(result);
}

TEST_F(CLManagerTest, PayReturnsFalseWhenInvalidCard) {
    // Bank에 등록되지 않은 카드
    std::string invalidCard = "9999999999999999";
    auto method = std::make_unique<CardPay>(invalidCard);
    std::unique_ptr<Payment> payment = std::make_unique<Payment>(1, 1, std::move(method));

    CLManager &manager = CLManager::getInstance();
    bool result = manager.pay(payment);

    EXPECT_FALSE(result);
}