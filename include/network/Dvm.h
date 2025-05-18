#pragma once

#include <cmath>

struct Dvm {
  static int vmX, vmY, vmId;
  int x, y, id;

  double distance() const;
  bool operator<(const Dvm& other) const;
};