#pragma once
#include "ItemManager.h"
#include "Payment.h"
#include "PrepaymentStock.h"
#include "MessageFactory.h"
#include "CertificationCodeFactory.h"
#include "Dvm.h"
#include "NetworkManager.h"
#include <string>
#include <set>

enum class ORDER_STATUS { LOCAL, REMOTE, FAIL };

class CLManager {
  private:
    ItemManager *itemManager;
    PrepaymentStock *prepaymentStock;
    MessageFactory *messageFactory;
    CertificationCodeFactory *certificationCodeFactory;
    NetworkManager *networkManager;

    std::unique_ptr<std::set<Dvm>> dvmNavigator;

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
    ORDER_STATUS order(int itemCode, int quantity, const std::string &,
                       std::unique_ptr<Payment> &payment);
    bool pay(std::unique_ptr<Payment> &payment);
    std::optional < std::reference_wrapper<const Dvm>> prePay(
                        std::unique_ptr<Payment> &payment);
    optional<Payment> enterCertCode(string certCode);
};