#pragma once
#include "RemoteValidator.h"

class RemoteItemValidateAdapter : public RemoteValidator{
    // TODO network manager 추가 필요

    public:
    bool validate(const Payment& p) const override;
};