#include "Payment.h"
#include "RemoteValidator.h"
#include "LocalValidator.h"

void Payment::addItem(const std::string &name, int quantity)
{
    items.first = name;
    items.second = quantity;
}

void Payment::setPrepayCode(int code)
{
    prepayCode = code;
}

int Payment::getPrepayCode() const
{
    return prepayCode;
}

std::pair<std::string, int> Payment::getItems() const{
    return items;
}


std::map<std::type_index, bool> Payment::validate() const{
    std::map<std::type_index, bool> result;
    
    for (const auto& [type, validator] : validatorList){
        result[type] = validator -> validate(*this);
    }
}

bool Payment::canlocalbuy() const{
    for (const auto&  [type, ptr] : validatorList){
        if (dynamic_cast<const RemoteValidator*>(ptr.get())){
            continue;
        }
        if (!ptr->validate(*this)){
            return false;
        }
    }
    return true;
}

bool Payment::canremotebuy() const{
    for (const auto& [type, ptr] : validatorList){
        if (dynamic_cast<const LocalValidator*>(ptr.get())){
            continue;
        }
        if(!ptr->validate(*this)){
            return false;
        }
        return true;
    }
}


