#include <unistd.h>
#include <thread>

#include "NetworkManager.h"
#include "CLManager.h"

int main() {
  NetworkManager& networkManager = NetworkManager::getInstance();

  CLManager& clManager = CLManager::getInstance();

  std::thread serverThread(&NetworkManager::runServer, &networkManager);

  sleep(1);

  clManager.run();

  serverThread.detach();
  return 0;
}

