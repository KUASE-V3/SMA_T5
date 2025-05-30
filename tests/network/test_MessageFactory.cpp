#include <gtest/gtest.h>

#include "MessageFactory.h"

using namespace std;

TEST(MessageFactoryTest, CreateRequestStockJson) {

    MessageFactory &messageFactory = MessageFactory::getInstance();
    string msgType = "req_stock";
    int code = 1;
    int num = 20;
    nlohmann::json json = nlohmann::json::parse(messageFactory.createRequestStockJson(code, num));

    string foundMessage = json["msg_type"];
    int foundCode = json["msg_content"]["item_code"];
    int foundNum = json["msg_content"]["item_num"];

    EXPECT_EQ(msgType, foundMessage);
    EXPECT_EQ(code, foundCode);
    EXPECT_EQ(num, foundNum);
}

TEST(MessageFactoryTest, CreateRequestPrepayJson) {

    MessageFactory &messageFactory = MessageFactory::getInstance();
    string msgType = "req_stock";
    int destination = 6;
    int code = 4;
    int num = 5;
    string certficationCode = "5AAAA";

    nlohmann::json json = nlohmann::json::parse(
        messageFactory.createRequestPrepayJson(destination, code, num, certficationCode));

    string foundMessage = json["msg_type"];
    int foundDestination = json["dst_id"];
    int foundCode = json["msg_content"]["item_code"];
    int foundNum = json["msg_content"]["item_num"];
    string foundCertificationCode = json["msg_content"]["cert_code"];

    EXPECT_EQ(msgType, foundMessage);
    EXPECT_EQ(destination, foundDestination);
    EXPECT_EQ(code, foundCode);
    EXPECT_EQ(num, foundNum);
    EXPECT_EQ(certficationCode, foundCertificationCode);
}

TEST(MessageFactoryTest, CreateResponseStockJson) {
    MessageFactory &messageFactory = MessageFactory::getInstance();
    string msgType = "resp_stock";
    int destination = 6;
    int code = 1;
    int num = 20;
    int xCoor = 3;
    int yCoor = 4;
    nlohmann::json json = nlohmann::json::parse(
        messageFactory.createResponseStockJson(destination, code, num, xCoor, yCoor));

    string foundMessage = json["msg_type"];
    int foundDestination = json["dst_id"];
    int foundCode = json["msg_content"]["item_code"];
    int foundNum = json["msg_content"]["item_num"];
    int foundXCoor = json["msg_content"]["coor_x"];
    int foundYCoor = json["msg_content"]["coor_y"];

    EXPECT_EQ(msgType, foundMessage);
    EXPECT_EQ(destination, foundDestination);
    EXPECT_EQ(code, foundCode);
    EXPECT_EQ(num, foundNum);
    EXPECT_EQ(xCoor, foundXCoor);
    EXPECT_EQ(yCoor, foundYCoor);
}

TEST(MessageFactoryTest, CreateResponsePrepayJson) {
    MessageFactory &messageFactory = MessageFactory::getInstance();
    string msgType = "resp_prepay";
    int destination = 6;
    int code = 4;
    int num = 5;
    bool availability = true;

    nlohmann::json json = nlohmann::json::parse(
        messageFactory.createResponsePrepayJson(destination, code, num, availability));

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