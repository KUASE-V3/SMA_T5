#include "LocalItemValidateAdapter.h"
#include <iostream>
#include <optional>


bool LocalItemValidateAdapter::validate(const Payment &p) const {

    return itemManager->isValid(p.getItemCode(), p.getQuantity());
}