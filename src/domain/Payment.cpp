#include "Payment.h"
#include "ItemManager.h"
#include "LocalValidator.h"
#include "RemoteValidator.h"
#include "ValidatorFactory.h"
#include <algorithm>

void Payment::setCertCode(std::string code) {
    certCode = code;
}

std::string Payment::getCertCode() const {
    return certCode;
}

std::optional<int> Payment::getItemCode() const {
    return itemcode;
}

std::optional<int> Payment::getQuantity() const {
    return quantity;
}

bool Payment::canLocalBuy() const {
    if (!validate()){
        return false;
    }
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
    if (!validate()){
        return false;
    }
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

bool Payment::validate() const {
    for (const auto &[type, ptr] : validatorTypeList) {
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
    : itemcode(itemcode), quantity(quantity),
      validatorList(std::move(ValidatorFactory::getInstance().setValidatorFullList())),
      validatorTypeList(std::move(ValidatorFactory::getInstance().setValidatorTypeList())),
      buyContent(std::move(buytype)), certCode("") {}

Payment::Payment(int itemcode)
    : itemcode(itemcode),
      validatorTypeList(std::move(ValidatorFactory::getInstance().setValidatorItemList())),
      certCode("") {}

Payment::Payment(int itemcode, int quantity)
    : itemcode(itemcode), quantity(quantity),
      validatorTypeList(std::move(ValidatorFactory::getInstance().setValidatorItemList())),
      certCode("") {}

bool Payment::pay() {
    Bank &bank = Bank::getInstance();
    return bank.pay(*this);
}

int Payment::getTotalPrice() const {
    ItemManager &itemManager = ItemManager::getInstance();

    auto items = itemManager.getItems();
    auto it = std::find_if(items.begin(), items.end(),
                           [this](const Item &item) { return item.getCode() == this->itemcode; });

    if (it != items.end()) {
        return it->getPrice() * this->quantity.value();
    }

    return 0;
}
