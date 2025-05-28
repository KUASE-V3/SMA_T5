#include "Item.h"

#include <iomanip>
#include <iostream>
#include <cstdio>
#include <string>

Item::Item(int code, const std::string &name, int price, int count)
    : code(code), name(name), price(price), count(count) {}

std::string Item::toString() const {
  char buf[100];
  snprintf(buf, 100, "%2d) %-20s     가격 : %d    재고 : %d", code, name.c_str(), price, count);
  std::string str(buf);
  return str;
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

std::string Item::getName() const { return name; }

int Item::getPrice() const {
    return price;
}

bool Item::isValid(int reqCount) const {
    return reqCount <= 100 && count >= reqCount && reqCount >= 1;
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