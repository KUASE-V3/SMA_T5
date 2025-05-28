#include "ItemTypeValidateAdapter.h"

bool ItemTypeValidateAdapter::validate(const Payment &p) const {
    return Itemmanager.isValidType(p.getItemCode(), p.getQuantity());
}