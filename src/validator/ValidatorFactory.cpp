#include "ValidatorFactory.h"
#include <map>
#include <memory>
#include <typeindex>
#include <Validator.h>
#include "LocalItemValidateAdapter.h"
#include "RemoteItemValidateAdapter.h"
#include "CardPayValidateAdapter.h"
#include "ItemTypeValidateAdapter.h"

std::map<std::type_index, std::unique_ptr<Validator>> ValidatorFactory::setValidatorFullList() const{
    std::map<std::type_index, std::unique_ptr<Validator>> map;

    map[typeid(LocalItemValidateAdapter)] = std::make_unique<LocalItemValidateAdapter>();
    map[typeid(RemoteItemValidateAdapter)] = std::make_unique<RemoteItemValidateAdapter>();
    map[typeid(CardPayValidateAdapter)] = std::make_unique<CardPayValidateAdapter>();

    return map;
}

std::map<std::type_index, std::unique_ptr<Validator>> ValidatorFactory::setValidatorItemList() const{
    std::map<std::type_index, std::unique_ptr<Validator>> map;

    map[typeid(LocalItemValidateAdapter)] = std::make_unique<ItemTypeValidateAdapter>();
    return map;
}

std::map<std::type_index, std::unique_ptr<Validator>> ValidatorFactory::setValidatorTypeList() const{
    std::map<std::type_index, std::unique_ptr<Validator>> map;

    map[typeid(LocalItemValidateAdapter)] = std::make_unique<ItemTypeValidateAdapter>();
    map[typeid(CardPayValidateAdapter)] = std::make_unique<ItemTypeValidateAdapter>();
    return map;
}



