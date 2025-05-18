#pragma once

#include "Payment.h"
#include <optional>
#include <map>

using namespace std;

class PrepaymentStock {

    private:
     map<string, Payment> prepayments;
     PrepaymentStock();
     PrepaymentStock(const PrepaymentStock&) = delete;
     PrepaymentStock& operator=(const PrepaymentStock&) = delete;

    public:
     static PrepaymentStock& getInstance();
     void addPayment(string certCode, Payment& payment);
     optional<Payment> findPaymentBycertCode(string certCode);
};