#include "domain/CLManager.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

TEST(CLManagerTest, ShowItemsPrintsCorrectly) {
    CLManager clManager;

    // 출력 캡처
    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    clManager.showItems();

    std::cout.rdbuf(oldCout); // 복구

    std::string output = buffer.str();

    EXPECT_NE(output.find("콜라"), std::string::npos);
    EXPECT_NE(output.find("카페라떼"), std::string::npos);
    EXPECT_NE(output.find("1500"), std::string::npos);
    EXPECT_NE(output.find("2200"), std::string::npos);

    clManager.showItems();
}