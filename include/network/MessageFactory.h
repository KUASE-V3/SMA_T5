#pragma once
#include <string>
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

using namespace std;

class MessageFactory {
    private:
        MessageFactory();

        MessageFactory(const MessageFactory&) = delete;
        MessageFactory& operator=(const MessageFactory&) = delete;
        
    public:
         static MessageFactory& getInstance();
         string createRequestStockJson(int code, int num);

        string createRequestPrepayJson(int destination, int code, int num, int certificationCode);

        string createResponseStockJson(int destination, int code, int num, int xCoor, int yCoor);

        string createResponsePrepayJson(int destination, int code, int num, bool availability);
};