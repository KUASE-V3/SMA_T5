#pragma once
#include <string>
#include <unordered_map>

class Payment;

class Bank {
  private:
    std::unordered_map<std::string, int> cardBalanceMap;
    Bank();
    bool isValid(const std::string &cardInfo) const;
    bool hasEnoughBalance(const std::string &cardNumber, int amount) const;

  public:
    Bank(const Bank &) = delete;
    Bank &operator=(const Bank &) = delete;
    static Bank &getInstance();
    bool pay(const Payment &payment);
};