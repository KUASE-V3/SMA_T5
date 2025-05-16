#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Validator.h"
#include "PaymentMethod.h"

class Payment {
private:
    std::vector<std::pair<std::string, int>> items;
    std::vector<Validator> validatorList;
    //buy type
    PaymentMethod *buyContent;
    int certCode;

public:
    Payment() {

    }
    void addItem(const std::string& name, int quantity);
    std::vector<std::pair<std::string, int>> getItems() const;

    void setCertCode(int code);
    int getCertCode() const;
};