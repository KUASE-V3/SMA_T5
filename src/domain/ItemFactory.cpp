#include "ItemFactory.h"

std::vector<Item> ItemFactory::createInitialItems() {
    std::vector<Item> items;

    items.emplace_back(1, "콜라", 1500, 10);
    items.emplace_back(2, "사이다", 1500, 10);
    items.emplace_back(3, "녹차", 1300, 10);
    items.emplace_back(4, "홍차", 1300, 10);
    items.emplace_back(5, "밀크티", 2000, 10);
    items.emplace_back(6, "탄산수", 1200, 10);
    items.emplace_back(7, "보리차", 1000, 10);
    items.emplace_back(8, "캔커피", 1400, 10);
    items.emplace_back(9, "물", 800, 10);
    items.emplace_back(10, "에너지드링크", 2500, 10);
    items.emplace_back(11, "유자차", 1600, 10);
    items.emplace_back(12, "식혜", 1400, 10);
    items.emplace_back(13, "아이스티", 1500, 10);
    items.emplace_back(14, "딸기주스", 1800, 10);
    items.emplace_back(15, "오렌지주스", 1800, 10);
    items.emplace_back(16, "포도주스", 1800, 10);
    items.emplace_back(17, "이온음료", 1500, 10);
    items.emplace_back(18, "아메리카노", 2000, 10);
    items.emplace_back(19, "핫초코", 1900, 10);
    items.emplace_back(20, "카페라떼", 2200, 10);

    return items;
}