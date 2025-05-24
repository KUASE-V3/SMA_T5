#include "ItemFactory.h"
#include <string>

using namespace std;
using json = nlohmann::json;

json ItemFactory::itemList;

std::vector<Item> ItemFactory::createInitialItems() {
    std::vector<Item> items;

    for (int i = 1; i <= 20; i++)
    {
      string code = to_string(i);
      string name = itemList["item_list"][code]["item_name"];
      int price = itemList["item_list"][code]["price"];
      int num = itemList["item_list"][code]["item_num"];

      items.emplace_back(i, name, price, num);
    }
    return items;
}