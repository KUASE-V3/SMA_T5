#include "Payment.h"
#include "ItemManager.h"
#include "LocalValidator.h"
#include "RemoteValidator.h"
#include "ValidatorFactory.h"
#include <algorithm>

void Payment::setCertCode(int code) {
    certCode = code;
}

int Payment::getCertCode() const {
    return certCode;
}

std::pair<int, int> Payment::getOrder() const {
    return order;
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
    : order{itemcode, quantity},
      validatorList(std::move(ValidatorFactory::getInstance().setValidatorList())),
      buyContent(std::move(buytype)), certCode(0) {}

bool Payment::pay() {
    Bank &bank = Bank::getInstance();
    return bank.pay(*this);
}

int Payment::getTotalPrice() const {
    ItemManager &itemManager = ItemManager::getInstance();

    auto items = itemManager.getItems();
    auto it = std::find_if(items.begin(), items.end(), [this](const Item &item) {
        return item.getCode() == this->order.first;
    });

    if (it != items.end()) {
        return it->getPrice() * order.second;
    }

    return 0;
}
