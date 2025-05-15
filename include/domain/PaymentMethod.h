#pragma once

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual bool isValid() const = 0;
};