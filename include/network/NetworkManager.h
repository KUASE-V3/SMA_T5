#pragma once

#include <string>

using namespace std;

class NetworkManager {
    private:
     static const int PORT = 8080;
     NetworkManager();
     NetworkManager(const NetworkManager&) = delete;
     NetworkManager& operator=(const NetworkManager&) = delete;

    public:
        // static NetworkManager& getInstance();
        static string sendMessage(string message);
};

void runServer();