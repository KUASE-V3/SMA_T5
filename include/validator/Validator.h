#pragma once
#include <string>
#include <utility> // for std::pair

class Payment;

class Validator {
  public:
    virtual ~Validator() = default;
    virtual bool validate(const Payment& payment) const = 0;
};