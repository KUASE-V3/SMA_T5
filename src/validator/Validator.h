#pragma once
#include <string>
#include <utility> // for std::pair
#include "Payment.h"

class Validator {
public:
    virtual ~Validator() = default;
    virtual std::pair<std::string, bool> validate(const Payment& p) = 0;
};