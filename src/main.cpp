#include <unistd.h>
#include <thread>

#include "NetworkManager.h"

int main() {
  NetworkManager& networkManager = NetworkManager::getInstance();

  std::thread serverThread(&NetworkManager::runServer, &networkManager);

  sleep(1);

  // main

  serverThread.detach();
  return 0;
}

