#include <gtest/gtest.h>

#include "Payment.h"
#include "PrepaymentStock.h"

using namespace std;

TEST(PrepaymentStockTest, FindPaymentBycertCode) {
  PrepaymentStock& prepaymentStock = PrepaymentStock::getInstance();

  Payment payment(1, 1, nullptr);

  prepaymentStock.addPayment("5AAAA", payment);

  Payment foundPayment = prepaymentStock.findPaymentBycertCode("5AAAA").value();

  pair<int, int> item = payment.getOrder();
  pair<int, int> foundItem = foundPayment.getOrder();

  EXPECT_EQ(item, foundItem);
};

TEST(PrepaymentStockTest, CanNotFindPaymentBycertCode) {
  PrepaymentStock& prepaymentStock = PrepaymentStock::getInstance();

  Payment payment(1, 1, nullptr);

  prepaymentStock.addPayment("5AAAA", payment);

  optional<Payment> foundPayment = prepaymentStock.findPaymentBycertCode("5AAAB");

  EXPECT_FALSE(foundPayment.has_value());
}