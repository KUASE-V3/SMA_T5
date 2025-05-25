#include "LocalItemValidateAdapter.h"
#include <iostream>
#include <optional>

// LocalItemValidateAdapter::LocalItemValidateAdapter(ItemManager& manager)
//     : itemManager(manager) {}

// std::pair<std::string, bool> LocalItemValidateAdapter::validate(const Payment& p) {
//     for (const auto& [name, qty] : p.getItems()) {
//         Item* item = itemManager.findByName(name);
//         if (!item) {
//             return { "NAME_ERROR", false };
//         }
//         if (!item->isValid(qty)) {
//             return { "STOCK_ERROR", false };
//         }
//     }
//     return { "SUCCESS", true };
// }

bool LocalItemValidateAdapter::validate(const Payment &p) const {

    return itemManager->isValid(p.getItemCode().value(), p.getQuantity().value());
}