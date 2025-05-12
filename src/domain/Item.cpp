#include "Item.h"

Item::Item(const std::string& name, int price, int count)
    : name(name), price(price), count(count) {}

std::string Item::getName() const {
    return name;
}

int Item::getPrice() const {
    return price;
}

bool Item::isValid(int reqCount) const {
    return count >= reqCount;
}

bool Item::add(int addCount) {
    if (addCount <= 0) return false;
    count += addCount;
    return true;
}

bool Item::buy(int reqCount) {
    if (reqCount <= 0 || count < reqCount) return false;
    count -= reqCount;
    return true;
}