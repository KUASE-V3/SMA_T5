#pragma once
#include <mutex>
#include <string>

class Item {
  private:
    int code;
    std::string name;
    int price;
    int count;
    mutable std::mutex mtx;

   public:
    Item(int code, const std::string &name, int price, int count);

    Item(const Item& other);
    Item(Item&& other) noexcept;
    Item& operator=(Item&& other) noexcept;
    std::string toString() const;
    std::string getName() const;
    int getPrice() const;
    bool isValid(int reqCount) const;
    int getCode() const;
    bool add(int addCount);
    bool consume(int reqCount);
    int getCount() const;
};