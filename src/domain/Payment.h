#pragma once
#include <string>
#include <vector>
#include <utility>

class Payment {
private:
    std::vector<std::pair<std::string, int>> items;
    int prepayCode = -1;

public:
    void addItem(const std::string& name, int quantity);
    std::vector<std::pair<std::string, int>> getItems() const;

    void setPrepayCode(int code);
    int getPrepayCode() const;
};