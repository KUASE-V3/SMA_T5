#pragma once
#include "Bank.h"
#include "PaymentMethod.h"
#include "Validator.h"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <typeindex>
#include <utility>
#include <vector>

class Payment {
  private:
    std::optional<int> itemcode;
    std::optional<int> quantity;
    std::map<std::type_index, std::unique_ptr<Validator>> validatorList;
    std::map<std::type_index, std::unique_ptr<Validator>> validatorTypeList;
    // buy type
    std::unique_ptr<PaymentMethod> buyContent;
    std::string certCode;

  public:
    Payment(int itemcode, int quantity, std::unique_ptr<PaymentMethod> buyContent);
    Payment(int itemcode);
    Payment(int itemcode, int quantity);
    std::optional<int> getItemCode() const;
    std::optional<int> getQuantity() const;
    void setCertCode(std::string code);
    std::string getCertCode() const;
    const PaymentMethod *getbuyContent() const;
    bool canLocalBuy() const;
    bool canRemoteBuy() const;
    bool pay();
    int getTotalPrice() const;
    bool validate() const;
};