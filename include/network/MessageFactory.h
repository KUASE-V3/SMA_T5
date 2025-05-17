#pragma once
#include <string>
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

class MessageFactory {
    private:
        MessageFactory();

        MessageFactory(const MessageFactory&) = delete;
        MessageFactory& operator=(const MessageFactory&) = delete;
        
    public:
        // static MessageFactory& getInstance();
        static std::string createRequestStockJson(int code, int num) {
          json requestStockJson = {
              {"msg_type", "req_stock"},
              {"src_id", 5},
              {"dst_id", 0},
              {"msg_content", {{"item_code", code}, {"item_num", num}}}};

          return requestStockJson.dump();
        }

        static std::string createRequestPrepayJson(int destination, int code, int num, int certificationCode) {
          json requestPrepayJson = {
              {"msg_type", "req_prepay"},
              {"src_id", 5},  // TODO: 하드코딩 지우기
              {"dst_id", destination},
              {"msg_content", {
                {"item_code", code}, 
                {"item_num", num},
                {"cert_code", certificationCode}}}};

          return requestPrepayJson.dump();
        }

        static std::string createResponseStockJson(int destination, int code, int num, int xCoor, int yCoor) {
          json responseStockJson = {
              {"msg_type", "res_stock"},
              {"src_id", 5},
              {"dst_id", destination},
              {"msg_content", {
                {"item_code", code},
                {"item_num", num},
                {"coor_x", xCoor},
                {"coor_y", yCoor}
            }}};

          return responseStockJson.dump();
        }

        static std::string createResponsePrepayJson(int destination, int code, int num, bool availability) {
          json responsePrepayJson = {
            {"msg_type", "res_prepay"},
            {"src_id", 5},  // TODO: 하드코딩 지우기
            {"dst_id", destination},
            {"msg_content",
                {{"item_code", code},
                {"item_num", num},
                {"availability", availability}}}};

          return responsePrepayJson.dump();
        }
};