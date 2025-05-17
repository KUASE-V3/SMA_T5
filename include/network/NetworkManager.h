#pragma once

#include <map>
#include <string>

#include "ItemManager.h"
#include "PrepaymentStock.h"

using namespace std;

class NetworkManager {
    private:
     map<int, string> addresses;
     ItemManager* itemManager;
     PrepaymentStock* prepaymentStock;

     static const int PORT = 8080;
     NetworkManager();
     NetworkManager(const NetworkManager&) = delete;
     NetworkManager& operator=(const NetworkManager&) = delete;

    public:
        static NetworkManager& getInstance();
        string sendMessage(string message);
        void sendBroadcastMessage(string message);
        void runServer();
};

void runServer();