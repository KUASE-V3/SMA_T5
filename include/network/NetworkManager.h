#pragma once

#include <map>
#include <set>
#include <string>

#include "ItemManager.h"
#include "PrepaymentStock.h"
#include "MessageFactory.h"
#include "Dvm.h"

using namespace std;

class NetworkManager {
    private:
     map<int, string> addresses;
     ItemManager* itemManager;
     PrepaymentStock* prepaymentStock;
     MessageFactory* messageFactory;
     set<Dvm>* dvmNavigator;

     static const int PORT = 8080;
     NetworkManager();
     NetworkManager(const NetworkManager&) = delete;
     NetworkManager& operator=(const NetworkManager&) = delete;

    public:
        static NetworkManager& getInstance();
        string sendMessage(string message);
        bool sendBroadcastMessage(string message);
        void runServer();
        void setDvmNavigator(std::set<Dvm>* dvmNav);
};