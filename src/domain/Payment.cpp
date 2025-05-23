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

std::optional<int> Payment::getItemCode() const{
    return itemcode;
}

std::optional<int> Payment::getItemQuantity() const{
    return quantity;
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

bool Payment::validate() const {
    for (const auto &[type, ptr] : validatorList){
        if (!ptr->validate(*this)){
            return false;
        }
    }
    return true;
}

const PaymentMethod *Payment::getbuyContent() const {
    return buyContent.get();
}

Payment::Payment(int itemcode, int quantity, std::unique_ptr<PaymentMethod> buytype)
    : itemcode(itemcode),
      quantity(quantity),
      validatorList(std::move(ValidatorFactory::getInstance().setValidatorFullList())),
      buyContent(std::move(buytype)), certCode(0) {}

Payment::Payment(int itemcode)
    : itemcode(itemcode),
      validatorList(std::move(ValidatorFactory::getInstance().setValidatorItemList())),
      certCode(0) {}

Payment::Payment(int itemcode, int quantity)
    : itemcode(itemcode),
      quantity(quantity),
      validatorList(std::move(ValidatorFactory::getInstance().setValidatorItemList())),
      certCode(0) {}

bool Payment::pay() {
    Bank &bank = Bank::getInstance();
    return bank.pay(*this);
}

int Payment::getTotalPrice() const {
    ItemManager &itemManager = ItemManager::getInstance();

    auto items = itemManager.getItems();
    auto it = std::find_if(items.begin(), items.end(), [this](const Item &item) {
        return item.getCode() == this->itemcode;
    });

    if (it != items.end()) {
        return it->getPrice() * this->quantity.value();
    }

    return 0;
}
