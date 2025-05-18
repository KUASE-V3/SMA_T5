#pragma once

#include "Payment.h"
#include <optional>
#include <map>

using namespace std;

class PrepaymentStock {

    private:
     map<int, Payment> prepayments;
     PrepaymentStock();
     PrepaymentStock(const PrepaymentStock&) = delete;
     PrepaymentStock& operator=(const PrepaymentStock&) = delete;

    public:
     static PrepaymentStock& getInstance();
     void addPayment(int certCode, Payment& payment);
     optional<Payment> findPaymentBycertCode(int certCode);
};