#include "Item.h"
#include <iomanip>
#include <iostream>
#include <sstream>

Item::Item(int code, const std::string &name, int price, int count)
    : code(code), name(name), price(price), count(count) {}

std::string Item::toString() const {
    std::ostringstream oss;

    // ex: 01) 콜라       : 1500
    oss << std::setw(2) << std::setfill('0') << code << ") " << name << " : " << std::right
        << std::setw(4) << price;

    return oss.str();
}

std::string Item::getName() const {
    return name;
}

int Item::getPrice() const {
    return price;
}

// bool Item::isValid(int reqCount) const {
//     return count >= reqCount;
// }

// bool Item::add(int addCount) {
//     if (addCount <= 0) return false;
//     count += addCount;
//     return true;
// }

// bool Item::buy(int reqCount) {
//     if (reqCount <= 0 || count < reqCount) return false;
//     count -= reqCount;
//     return true;
// }
