#pragma once
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <typeindex>
#include "Validator.h"
#include "PaymentMethod.h"
#include <memory>

class Payment {
private:
    std::pair<std::string, int> items;
    std::map<std::type_index, std::unique_ptr<Validator>> validatorList;
    //buy type
    PaymentMethod *buyContent;
    int certCode;
    std::map<std::type_index, bool> validate() const;
    
public:
    Payment() {

    }
    void addItem(const std::string& name, int quantity);
    std::pair<std::string, int> getItems() const;

    void setCertCode(int code);
    int getCertCode() const;
    PaymentMethod* getbuyContent() const;
    bool canlocalbuy() const;
    bool canremotebuy() const;
};