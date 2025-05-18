#include "PrepaymentStock.h"
#include <optional>

PrepaymentStock::PrepaymentStock() {};

PrepaymentStock& PrepaymentStock::getInstance() {
    static PrepaymentStock instance;
    return instance;
};

void PrepaymentStock::addPayment(int certCode, Payment& payment) {
  prepayments.emplace(certCode, move(payment));
}

optional<Payment> PrepaymentStock::findPaymentBycertCode(int certCode) {
  auto it = prepayments.find(certCode);
  if (it != prepayments.end()) {
    Payment payment = move(it->second);
    prepayments.erase(it);
    return payment;
  }
  return nullopt;
}