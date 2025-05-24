#include "Dvm.h"

int Dvm::vmX;
int Dvm::vmY;
// TODO: 팀명 T5
int Dvm::vmId;
int Dvm::portNumber;

double Dvm::distance() const {
  return std::hypot(x - vmX, y - vmY);
}

bool Dvm::operator<(const Dvm& other) const {
  double d1 = distance();
  double d2 = other.distance();
  if (d1 != d2) return d1 < d2;
  return id < other.id;
}
