#include "ValidatorFactory.h"
#include <map>
#include <memory>
#include <typeindex>
#include <Validator.h>
#include "LocalItemValidateAdapter.h"
#include "RemoteItemValidateAdapter.h"
#include "CardPayValidateAdapter.h"

std::map<std::type_index, std::unique_ptr<Validator>> ValidatorFactory::setValidatorList() const{
    std::map<std::type_index, std::unique_ptr<Validator>> map;

    map[typeid(LocalItemValidateAdapter)] = std::make_unique<LocalItemValidateAdapter>();
    map[typeid(RemoteItemValidateAdapter)] = std::make_unique<RemoteItemValidateAdapter>();
    map[typeid(CardPayValidateAdapter)] = std::make_unique<CardPayValidateAdapter>();

    return map;
}