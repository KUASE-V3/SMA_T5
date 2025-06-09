#pragma once

#include "Payment.h"
#include <optional>
#include <map>

class PrepaymentStock {

    private:
     std::map<std::string, Payment> prepayments;
     PrepaymentStock();
     PrepaymentStock(const PrepaymentStock&) = delete;
     PrepaymentStock& operator=(const PrepaymentStock&) = delete;

    public:
     static PrepaymentStock& getInstance();
     void addPayment(std::string certCode, Payment& payment);
     std::optional<Payment> findPaymentBycertCode(std::string certCode);
};