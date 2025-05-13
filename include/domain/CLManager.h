#pragma once
#include <string>
#include "ItemManager.h"
#include "Payment.h"

class CLManager {
private:
    ItemManager itemManager;
public:
    void showItems();
    void buy(const std::string& itemName, int quantity);
    void pay();
    void prePay(Payment& payment);
    void enterPrePayCode();
};