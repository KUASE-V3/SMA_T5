#include "CardPayValidateAdapter.h"
#include "Payment.h"

bool CardPayValidateAdapter::validate(const Payment& p) const {
    if (const auto* card = dynamic_cast<const CardPay*>(p.getbuyContent())) {
        return card->isValid();
    }
    return true;
}