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
    std::pair<int, int> items;
    std::map<std::type_index, std::unique_ptr<Validator>> validatorList;
    //buy type
    std::unique_ptr<PaymentMethod> buyContent;
    int prepayCode;
    
public:
    Payment(int itemcode, int quantity, std::unique_ptr<PaymentMethod> buytype);
    std::pair<int, int> getItems() const;
    void setPrepayCode(int code);
    int getPrepayCode() const;
    const PaymentMethod* getbuyContent() const;
    bool canlocalbuy() const;
    bool canremotebuy() const;
};