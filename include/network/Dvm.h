#pragma once

#include <cmath>

struct Dvm {
  static int vmX;
  static int vmY;
  static int vmId;

  int x;
  int y;
  int id;

  double distance() const;
  bool operator<(const Dvm& other) const;
};