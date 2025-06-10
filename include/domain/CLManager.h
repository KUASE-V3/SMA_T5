#pragma once

#include "CertificationCodeFactory.h"
#include "Dvm.h"
#include "ItemManager.h"
#include "MessageFactory.h"
#include "NetworkManager.h"
#include "Payment.h"
#include "PrepaymentStock.h"
#include <memory>
#include <optional>
#include <set>
#include <string>

enum class ORDER_STATUS { LOCAL, REMOTE, FAIL };

class CLManager {
  private:
    // Singleton dependencies
    ItemManager *itemManager;
    PrepaymentStock *prepaymentStock;
    MessageFactory *messageFactory;
    CertificationCodeFactory *certificationCodeFactory;
    NetworkManager *networkManager;

    std::unique_ptr<std::set<Dvm>> dvmNavigator;

    // Input
    int readInt(std::string text);
    std::string readString(std::string text);
    int promptValidItemCode();
    int promptValidQuantity(int itemCode);

    // Flow control
    void handleMenu(int select);
    void processOrder();
    void checkPrepaymentCode();

    // Order handling
    void handleLocalPayment(std::unique_ptr<Payment> payment);
    void handleRemotePayment(std::unique_ptr<Payment> payment);

    // Singleton enforcement
    CLManager();
    CLManager(const CLManager &) = delete;
    CLManager &operator=(const CLManager &) = delete;

  public:
    static CLManager &getInstance();

    void run();
    void showItems();

    ORDER_STATUS order(std::unique_ptr<Payment> &payment);
    bool pay(std::unique_ptr<Payment> &payment);
    std::optional<std::reference_wrapper<const Dvm>> prePay(std::unique_ptr<Payment> &payment);
    std::optional<Payment> enterCertCode(std::string certCode);
};