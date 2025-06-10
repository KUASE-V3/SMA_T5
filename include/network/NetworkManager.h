#pragma once

#include <map>
#include <set>
#include <string>

#include "ItemManager.h"
#include "PrepaymentStock.h"
#include "MessageFactory.h"
#include "Dvm.h"
#include "Address.h"

class NetworkManager {
    private:
     std::map<int, Address> addresses;
     ItemManager* itemManager;
     PrepaymentStock* prepaymentStock;
     MessageFactory* messageFactory;
     std::set<Dvm>* dvmNavigator;

     NetworkManager();
     NetworkManager(const NetworkManager&) = delete;
     NetworkManager& operator=(const NetworkManager&) = delete;

    public:
     static NetworkManager& getInstance();
     std::string sendMessage(const std::string& message);
     bool sendBroadcastMessage(const std::string& message);
     void runServer();
     void setDvmNavigator(std::set<Dvm>* dvmNav);
};