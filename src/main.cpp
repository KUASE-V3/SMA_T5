#include <thread>
#include <unistd.h>
#include <fstream>
#include <iostream>

#include "CLManager.h"
#include "NetworkManager.h"
#include "ItemManager.h"
#include "ItemFactory.h"

using json = nlohmann::json;

void init(char* fileName) {
  ifstream file(fileName, std::ios::in);

  json j;

  if (!file.is_open()) {
    std::cerr << "Error opening file.\n";
    return;
  }

  file >> j;
  Dvm::vmId = j["dvm_id"];
  Dvm::vmX = j["dvm_x"];
  Dvm::vmY = j["dvm_y"];
  Dvm::portNumber = j["port_number"];

  ItemFactory::itemList = j;
}

void updateJson(char* fileName) {
  std::ofstream file(fileName);

  if (!file) {
    std::cerr << "Error opening file.\n";
    return;
  }

  ItemManager &itemManager = ItemManager::getInstance();

  for (auto item : itemManager.getItems()) {
    ItemFactory::itemList["item_list"][to_string(item.getCode())]["item_num"] =
        item.getCount();
  }

  file << ItemFactory::itemList;
}

int main(int argc, char* argv[]) {

  if(argc != 2) {

    return -1;
  }

  init(argv[1]);
  NetworkManager& networkManager = NetworkManager::getInstance();
  CLManager& clManager = CLManager::getInstance();

    std::thread serverThread(&NetworkManager::runServer, &networkManager);

    sleep(1);

    clManager.run();

    serverThread.detach();
    return 0;

}
