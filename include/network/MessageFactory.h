#pragma once
#include <string>
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

class MessageFactory {
    private:
        MessageFactory() = default;

        MessageFactory(const MessageFactory&) = delete;
        MessageFactory& operator=(const MessageFactory&) = delete;
        
    public:
         static MessageFactory& getInstance();
         std::string createRequestStockJson(int code, int num) const;

        std::string createRequestPrepayJson(int destination, int code, int num, std::string certificationCode) const;

        std::string createResponseStockJson(int destination, int code, int num, int xCoor, int yCoor) const;

        std::string createResponsePrepayJson(int destination, int code, int num, bool availability) const;
};