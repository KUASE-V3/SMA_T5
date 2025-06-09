#pragma once
#include <typeindex>
#include <map>
#include <memory>
#include <Validator.h>


class ValidatorFactory{
    private:
    ValidatorFactory() = default;

    public:
    static ValidatorFactory& getInstance(){
        static ValidatorFactory instance;
        return instance;
    }
    ValidatorFactory(const ValidatorFactory&) = delete;
    ValidatorFactory& operator = (const ValidatorFactory&) = delete;
    std::map<std::type_index, std::unique_ptr<Validator>> setValidatorFullList() const;
    std::map<std::type_index, std::unique_ptr<Validator>> setValidatorItemList() const;
    std::map<std::type_index, std::unique_ptr<Validator>> setValidatorTypeList() const;
};