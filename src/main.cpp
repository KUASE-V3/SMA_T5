#include <iostream>
#include "json.hpp"

int main() {
    nlohmann::json jsonData;
    jsonData["Name"] = "Junkyu";
    jsonData["Age"] = "26";

    std::cout << jsonData << std::endl;
    return 0;
}