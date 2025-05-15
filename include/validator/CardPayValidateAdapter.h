#pragma once
#include "Validator.h"
#include "PaymentMethod.h"
#include "CardPay.h"
class CardPayValidateAdapter : public Validator{
    public:
    bool validate(const Payment& p) const override;
};