#include "RemoteItemValidateAdapter.h"

bool RemoteItemValidateAdapter::validate(const Payment &p) const {
    std::string requestMessage =
        messageFactory->createRequestStockJson(p.getItemCode().value(), p.getQuantity().value());
    return networkManager->sendBroadcastMessage(requestMessage);
};