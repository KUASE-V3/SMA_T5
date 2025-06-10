#include "Item.h"

#include <iomanip>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

Item::Item(int code, const std::string &name, int price, int count)
    : code(code), name(name), price(price), count(count) {}

std::string Item::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << code << ") "
        << std::left << std::setw(20) << name
        << "     가격 : " << price
        << "    재고 : " << count;
    return oss.str();
}


Item::Item(const Item& other)
    : code(other.code),
      name(other.name),
      price(other.price),
      count(other.count) {
}

Item::Item(Item&& other) noexcept
    : code(other.code),
      name(std::move(other.name)),
      price(other.price),
      count(other.count) {}

Item& Item::operator=(Item&& other) noexcept {
  if (this != &other) {
    code = other.code;
    name = std::move(other.name);
    price = other.price;
    count = other.count;
  }
  return *this;
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        std::scoped_lock lock(mtx, other.mtx);
        code = other.code;
        name = other.name;
        price = other.price;
        count = other.count;
    }
    return *this;
}

std::string Item::getName() const { return name; }

int Item::getPrice() const {
    return price;
}

bool Item::isValidType(int reqCount) const{
    return reqCount >= 1 && reqCount < 100;
}

bool Item::isValid(int reqCount) const {
    return count >= reqCount;
}

int Item::getCode() const {
    return code;
}
bool Item::add(int addCount) {
  std::lock_guard<std::mutex> lock(mtx);
  if (addCount <= 0) return false;
  count += addCount;
  return true;
}

bool Item::consume(int reqCount) {
  std::lock_guard<std::mutex> lock(mtx);
  if (reqCount <= 0 || count < reqCount) return false;
  count -= reqCount;
  return true;
}

int Item::getCount() const {
    return count;
}

Item::~Item() = default;