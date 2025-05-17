#pragma once
#include "Bank.h"
#include "PaymentMethod.h"
#include "Validator.h"
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <utility>
#include <vector>

class Payment {
  private:
    std::pair<int, int> order;
    std::map<std::type_index, std::unique_ptr<Validator>> validatorList;
    // buy type
    std::unique_ptr<PaymentMethod> buyContent;
    int prepayCode;

  public:
    Payment(int itemcode, int quantity, std::unique_ptr<PaymentMethod> buyContent);
    std::pair<int, int> getOrder() const;
    void setPrepayCode(int code);
    int getPrepayCode() const;
    const PaymentMethod *getbuyContent() const;
    bool canLocalBuy() const;
    bool canRemoteBuy() const;
    bool pay();
    int getTotalPrice() const;
};