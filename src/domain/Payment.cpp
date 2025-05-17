#include "Payment.h"
#include "LocalValidator.h"
#include "RemoteValidator.h"
#include "ValidatorFactory.h"

void Payment::setCertCode(int code) {
    certCode = code;
}

int Payment::getCertCode() const {
    return certCode;
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
      buyContent(std::move(buytype)), certCode(0) {}
