#pragma once
#include "NetworkManager.h"
#include "RemoteValidator.h"

class RemoteItemValidateAdapter : public RemoteValidator{
    private:
     NetworkManager* networkManager = &NetworkManager::getInstance();
     MessageFactory* messageFactory = &MessageFactory::getInstance();

    public:
    bool validate(const Payment& p) const override;
};