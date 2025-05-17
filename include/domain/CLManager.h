#pragma once
#include "ItemManager.h"
#include "Payment.h"
#include <string>

enum class ORDER_STATUS { LOCAL, REMOTE, FAIL };

class CLManager {
  private:
    ItemManager itemManager;
    int readInt(std::string text);

    // 싱글톤
    CLManager();
    CLManager(const CLManager &) = delete;
    CLManager &operator=(const CLManager &) = delete;

  public:
    // 싱글톤 인스턴스
    static CLManager &getInstance();
    void run();
    void showItems();
    ORDER_STATUS order(int code, int quantity, std::string card);
    void pay();
    void prePay(Payment &payment);
    void enterPrePayCode();
};