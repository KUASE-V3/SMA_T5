#pragma once
#include "ItemManager.h"
#include "Payment.h"
#include "PrepaymentStock.h"
#include <string>

enum class ORDER_STATUS { LOCAL, REMOTE, FAIL };

class CLManager {
  private:
    ItemManager *itemManager;
    PrepaymentStock *prepaymentStock;

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
    // CLManager.h
    ORDER_STATUS order(int itemCode, int quantity, const std::string &card,
                       std::unique_ptr<Payment> &payment);
    bool pay(std::unique_ptr<Payment> &payment);
    void prePay(Payment &payment);
    optional<Payment> enterCertCode(int certCode);
};