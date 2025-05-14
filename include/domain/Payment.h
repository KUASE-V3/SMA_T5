#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Validator.h"
#include "PaymentMethod.h"
#include <memory>

class Payment {
private:
    std::pair<std::string, int> items;
    std::vector<std::unique_ptr<Validator>> validatorList;
    //buy type
    PaymentMethod *buyContent;
    int prepayCode;

public:
    Payment() {

    }
    void addItem(const std::string& name, int quantity);
    std::pair<std::string, int> getItems() const;

    void setPrepayCode(int code);
    int getPrepayCode() const;
};