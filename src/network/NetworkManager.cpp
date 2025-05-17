#include "NetworkManager.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include "json.hpp"
#include "MessageFactory.h"
#include "Payment.h"
#include "LocalItemValidateAdapter.h"

using namespace std;

using json = nlohmann::json;


NetworkManager::NetworkManager() {
  addresses.emplace(1, "127.0.0.1");
  addresses.emplace(2, "127.0.0.1");
  addresses.emplace(3, "127.0.0.1");
  addresses.emplace(4, "127.0.0.1");
  addresses.emplace(5, "127.0.0.1");
  addresses.emplace(6, "127.0.0.1");
  addresses.emplace(7, "127.0.0.1");
  itemManager = &ItemManager::getInstance();
  prepaymentStock = &PrepaymentStock::getInstance();
}

NetworkManager& NetworkManager::getInstance() {
    static NetworkManager instance;
    return instance;
}

string NetworkManager::sendMessage(string message) {
  int sock = 0;
  char buffer[1024] = {0};
  sockaddr_in serverAddress{};

  json jsonMessage = json::parse(message);

  string address = addresses.find(jsonMessage["dst_id"])->second;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation error");
    return nullptr;
  }

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  if (inet_pton(AF_INET, address.c_str(), &serverAddress.sin_addr) <= 0) {
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

void NetworkManager::sendBroadcastMessage(string message) {
  for (pair<int, string> iter : addresses) {
    int sock = 0;
    char buffer[1024] = {0};
    sockaddr_in serverAddress{};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
      perror("Socket creation error");
      return;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    const char *address = iter.second.c_str();

    if (inet_pton(AF_INET, address, &serverAddress.sin_addr) <= 0) {
      perror("Invalid address / Address not supported");
      return;
    }

    if (connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
      perror("Connection Failed");
      return;
    }

    const char* msg = message.c_str();

    send(sock, msg, strlen(msg), 0);

    read(sock, buffer, sizeof(buffer));

    json responseJson = json::parse(buffer);

    close(sock);
  }
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

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

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
      // TODO xCoor, yCoor, 재고 확인 이후 어떻게 알려줌??

      responseMessage = MessageFactory::createResponseStockJson(requestMessage["src_id"],
                                              requestMessage["msg_content"]["item_code"], 
                                              requestMessage["msg_content"]["item_num"], 5, 5);

    } else if (msgType == "req_prepay") {
      int code = requestMessage["msg_content"]["item_code"];
      int num = requestMessage["msg_content"]["item_num"];
      Payment payment(code, num, nullptr);

      LocalItemValidateAdapter adapter;

      bool availability = adapter.validate(payment);

      if(availability) {
        if(itemManager->decreaseStock(code, -num)) {
          int certCode = requestMessage["msg_content"]["cert_code"];
          prepaymentStock->addPayment(certCode, payment);
        } else {
          availability = false;
        }
      }

      responseMessage = MessageFactory::createResponsePrepayJson(requestMessage["src_id"],
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