#include "Payment.h"
#include "LocalValidator.h"
#include "RemoteValidator.h"
#include "ValidatorFactory.h"

void Payment::setPrepayCode(int code) {
    prepayCode = code;
}

int Payment::getPrepayCode() const {
    return prepayCode;
}

std::pair<int, int> Payment::getItems() const {
    return items;
}

bool Payment::canLocalBuy() const {
    for (const auto &[type, ptr] : validatorList) {
        if (dynamic_cast<const RemoteValidator *>(ptr.get())) {
            continue;
        }
        if (!ptr->validate(*this)) {
            return false;
        }
    }
    return true;
}

bool Payment::canRemoteBuy() const {
    for (const auto &[type, ptr] : validatorList) {
        if (dynamic_cast<const LocalValidator *>(ptr.get())) {
            continue;
        }
        if (!ptr->validate(*this)) {
            return false;
        }
    }
    return true;
}

const PaymentMethod *Payment::getbuyContent() const {
    return buyContent.get();
}

Payment::Payment(int itemcode, int quantity, std::unique_ptr<PaymentMethod> buytype)
    : items{itemcode, quantity},
      validatorList(std::move(ValidatorFactory::getInstance().setValidatorList())),
      buyContent(std::move(buytype)), prepayCode(0) {}
