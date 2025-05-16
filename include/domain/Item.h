#pragma once
#include <string>

class Item {
  private:
    int code;
    std::string name;
    int price;
    int count;

  public:
    Item(int code, const std::string &name, int price, int count);

    std::string toString() const;
    std::string getName() const;
    int getPrice() const;
    bool isValid(int reqCount) const;
    // bool add(int addCount);
    // bool buy(int reqCount);
};