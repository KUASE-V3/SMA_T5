#include "RemoteItemValidateAdapter.h"

bool RemoteItemValidateAdapter::validate(const Payment& p) const{
  string requestMessage = messageFactory->createRequestStockJson(p.getItemCode().value(), p.getItemQuantity().value());
  return networkManager->sendBroadcastMessage(requestMessage);
};