#include <gtest/gtest.h>

#include "Dvm.h"
#include <set>

TEST(DvmTest, Distance){
    // 이 vm 좌표 설정
    Dvm::vmX = 0;
    Dvm::vmY = 0;
    Dvm::vmId = 5;

    Dvm dvm{3, 4, 1};
    double distance = dvm.distance();
    EXPECT_EQ(distance, 5);
};

TEST(DvmTest, canSortDvm){
  Dvm::vmX = 0;
  Dvm::vmY = 0;
  Dvm::vmId = 5;

  std::set<Dvm> set;
  set.insert({0, 10, 4});
  set.insert({3, 0, 1});
  set.insert({5, 0, 3});
  set.insert({3, 4, 2});

  int i = 1;
  for (auto dvm : set) {
    EXPECT_EQ(dvm.id, i);
    i++;
  }
};