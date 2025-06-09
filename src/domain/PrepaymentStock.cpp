#include "PrepaymentStock.h"
#include <optional>

using namespace std;

PrepaymentStock::PrepaymentStock() {};

PrepaymentStock& PrepaymentStock::getInstance() {
    static PrepaymentStock instance;
    return instance;
};

void PrepaymentStock::addPayment(string certCode, Payment& payment) {
  prepayments.emplace(certCode, move(payment));
}

optional<Payment> PrepaymentStock::findPaymentBycertCode(string certCode) {
  auto it = prepayments.find(certCode);
  if (it != prepayments.end()) {
    Payment payment = move(it->second);
    prepayments.erase(it);
    return payment;
  }
  return nullopt;
}