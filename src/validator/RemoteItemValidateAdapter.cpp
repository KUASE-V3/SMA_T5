#include "RemoteItemValidateAdapter.h"

bool RemoteItemValidateAdapter::validate(const Payment& p) const{
  pair<int, int> order = p.getOrder();
  string requestMessage = messageFactory->createRequestStockJson(order.first, order.second);
  return networkManager->sendBroadcastMessage(requestMessage);
};