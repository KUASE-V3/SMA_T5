#include <gtest/gtest.h>

#include "Payment.h"
#include "PrepaymentStock.h"

using namespace std;

TEST(PrepaymentStockTest, FindPaymentBycertCode) {
  PrepaymentStock& prepaymentStock = PrepaymentStock::getInstance();

  Payment payment(1, 1, nullptr);

  prepaymentStock.addPayment(5001, payment);

  Payment foundPayment = prepaymentStock.findPaymentBycertCode(5001).value();

  pair<int, int> item = payment.getItems();
  pair<int, int> foundItem = foundPayment.getItems();

  EXPECT_EQ(item, foundItem);
};

TEST(PrepaymentStockTest, CanNotFindPaymentBycertCode) {
  PrepaymentStock& prepaymentStock = PrepaymentStock::getInstance();

  Payment payment(1, 1, nullptr);

  prepaymentStock.addPayment(5001, payment);

  optional<Payment> foundPayment = prepaymentStock.findPaymentBycertCode(5002);

  EXPECT_FALSE(foundPayment.has_value());
}