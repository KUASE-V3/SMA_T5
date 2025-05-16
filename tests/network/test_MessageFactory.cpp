#include <gtest/gtest.h>

#include "MessageFactory.h"

using namespace std;

TEST(MessageFactoryTest, CreateRequestStockJson) {
  string msgType = "req_stock";
  int code = 1;
  int num = 20;
  nlohmann::json json = nlohmann::json::parse(MessageFactory::createRequestStockJson(code, num));

  string foundMessage = json["msg_type"];
  int foundCode = json["msg_content"]["item_code"];
  int foundNum = json["msg_content"]["item_num"];

  EXPECT_EQ(msgType, foundMessage);
  EXPECT_EQ(code, foundCode);
  EXPECT_EQ(num, foundNum);
}

TEST(MessageFactoryTest, CreateRequestPrepayJson) {
  string msgType = "req_stock";
  int destination = 6;
  int code = 4;
  int num = 5;
  int certficationCode = 5001;

  nlohmann::json json = nlohmann::json::parse(
      MessageFactory::createRequestPrepayJson(destination, code, num, certficationCode));

  string foundMessage = json["msg_type"];
  int foundDestination = json["dst_id"];
  int foundCode = json["msg_content"]["item_code"];
  int foundNum = json["msg_content"]["item_num"];
  int foundCertificationCode = json["msg_content"]["cert_code"];

  EXPECT_EQ(msgType, foundMessage);
  EXPECT_EQ(destination, foundDestination);
  EXPECT_EQ(code, foundCode);
  EXPECT_EQ(num, foundNum);
  EXPECT_EQ(certficationCode, foundCertificationCode);
}

TEST(MessageFactoryTest, CreateResponseStockJson) {
  string msgType = "res_stock";
  int code = 1;
  int num = 20;
  int xCoor = 3;
  int yCoor = 4;
  nlohmann::json json = nlohmann::json::parse(
      MessageFactory::createResponseStockJson(code, num, xCoor, yCoor));

  string foundMessage = json["msg_type"];
  int foundCode = json["msg_content"]["item_code"];
  int foundNum = json["msg_content"]["item_num"];
  int foundXCoor = json["msg_content"]["coor_x"];
  int foundYCoor = json["msg_content"]["coor_y"];

  EXPECT_EQ(msgType, foundMessage);
  EXPECT_EQ(code, foundCode);
  EXPECT_EQ(num, foundNum);
  EXPECT_EQ(xCoor, foundXCoor);
  EXPECT_EQ(yCoor, foundYCoor);
}

TEST(MessageFactoryTest, CreateResponsePrepayJson) {
  string msgType = "res_stock";
  int destination = 6;
  int code = 4;
  int num = 5;
  bool availability = true;

  nlohmann::json json =
      nlohmann::json::parse(MessageFactory::createResponsePrepayJson(destination, code, num, availability));

  string foundMessage = json["msg_type"];
  int foundDestination = json["dst_id"];
  int foundCode = json["msg_content"]["item_code"];
  int foundNum = json["msg_content"]["item_num"];
  int foundAvailability = json["msg_content"]["availability"];

  EXPECT_EQ(msgType, foundMessage);
  EXPECT_EQ(destination, foundDestination);
  EXPECT_EQ(code, foundCode);
  EXPECT_EQ(num, foundNum);
  EXPECT_TRUE(foundAvailability);
}