#include "CardPayValidateAdapter.h"
#include "Payment.h"

bool CardPayValidateAdapter::validate(const Payment& p) const {
    const CardPay* card = dynamic_cast<const CardPay*>(p.getbuyContent());
    if (card){
        return card->isValid();
    }
    return true;
}