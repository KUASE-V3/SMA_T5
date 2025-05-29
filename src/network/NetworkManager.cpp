#include "NetworkManager.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include "json.hpp"
#include "Payment.h"
#include "LocalItemValidateAdapter.h"
#include "Dvm.h"

using namespace std;

using json = nlohmann::json;

NetworkManager::NetworkManager() {
  // addresses.emplace(1, Address{"127.0.0.1", 1111});
  // addresses.emplace(2, Address{"127.0.0.1", 2020});
  // addresses.emplace(3, Address{"127.0.0.1", 3030});
  // addresses.emplace(4, Address{"127.0.0.1", 4040});
  addresses.emplace(5, Address{"127.0.0.1", 5050});
  addresses.emplace(6, Address{"127.0.0.1", 6060});
  addresses.emplace(7, Address{"127.0.0.1", 7070});
  itemManager = &ItemManager::getInstance();
  prepaymentStock = &PrepaymentStock::getInstance();
  messageFactory = &MessageFactory::getInstance();
  dvmNavigator = nullptr;
}

NetworkManager& NetworkManager::getInstance() {
  static NetworkManager instance;
  return instance;
}

void NetworkManager::setDvmNavigator(std::set<Dvm>* dvmNav) { dvmNavigator = dvmNav; }

string NetworkManager::sendMessage(string message) {
  int sock = 0;
  char buffer[1024] = {0};
  sockaddr_in serverAddress{};

  json jsonMessage = json::parse(message);

  auto address = addresses.find(jsonMessage["dst_id"]);

  string ipAddress = address->second.address;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation error");
    return nullptr;
  }

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(address->second.portNumber);

  if (inet_pton(AF_INET, address->second.address.c_str(), &serverAddress.sin_addr) <= 0) {
    perror("Invalid address / Address not supported");
    return nullptr;
  }

  if (connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
    perror("Connection Failed");
    return nullptr;
  }

  const char* msg = message.c_str();

  send(sock, msg, strlen(msg), 0);

  read(sock, buffer, sizeof(buffer));

  close(sock);

  return buffer;
}

bool NetworkManager::sendBroadcastMessage(string message) {
  bool canPrepay = false;
  for (pair<int, Address> iter : addresses) {
    if (iter.first == Dvm::vmId) continue;
    int sock = 0;
    char buffer[1024] = {0};
    sockaddr_in serverAddress{};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
      perror("Socket creation error");
      return canPrepay;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(iter.second.portNumber);

    const char *address = iter.second.address.c_str();

    if (inet_pton(AF_INET, address, &serverAddress.sin_addr) <= 0) {
      perror("Invalid address / Address not supported");
      return canPrepay;
    }

    if (connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
      perror("Connection Failed");
      return canPrepay;
    }

    const char* msg = message.c_str();

    send(sock, msg, strlen(msg), 0);

    read(sock, buffer, sizeof(buffer));

    json responseJson = json::parse(buffer);

    if(responseJson["msg_content"]["item_code"] != 0) {
      canPrepay = true;
      dvmNavigator->insert({responseJson["msg_content"]["coor_x"], responseJson["msg_content"]["coor_y"], responseJson["src_id"]});
    }

    close(sock);
  }
  return canPrepay;
}

void NetworkManager::runServer() {
  int server_fd, client_fd;
  sockaddr_in address{};
  int addrlen = sizeof(address);
  char buffer[1024] = {0};

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) {
    perror("socket failed");
    return;
  }

  auto myAddress = addresses.find(Dvm::vmId);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(myAddress->second.portNumber);

  if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
    perror("bind failed");
    return;
  }

  listen(server_fd, 3);

  while (true) {
    client_fd = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);
    if (client_fd < 0) {
      perror("accept");
      continue;
    }

    memset(buffer, 0, sizeof(buffer));
    read(client_fd, buffer, sizeof(buffer));

    json requestMessage = json::parse(buffer);

    string msgType = requestMessage["msg_type"];

    string responseMessage;

    if (msgType == "req_stock") {
      int code = requestMessage["msg_content"]["item_code"];
      int num = requestMessage["msg_content"]["item_num"];
      if (!itemManager->isValid(code, num)) {
        code = 0;
        num = 0;
      }

      responseMessage = messageFactory->createResponseStockJson(
          requestMessage["src_id"], code, num, Dvm::vmX, Dvm::vmY);

    } else if (msgType == "req_prepay") {
      int code = requestMessage["msg_content"]["item_code"];
      int num = requestMessage["msg_content"]["item_num"];
      Payment payment(code, num, nullptr);

      bool availability = itemManager->isValid(code, num);

      if(availability) {
        if (itemManager->decreaseStock(code, num)) {
          string certCode = requestMessage["msg_content"]["cert_code"];
          prepaymentStock->addPayment(certCode, payment);
        } else {
          availability = false;
        }
      }

      responseMessage = messageFactory->createResponsePrepayJson(requestMessage["src_id"],
                                               requestMessage["msg_content"]["item_code"],
                                               requestMessage["msg_content"]["item_num"], availability);

    } else {
      // err
    }

    send(client_fd, responseMessage.c_str(), responseMessage.size(), 0);

    close(client_fd);
  }

  close(server_fd);
}