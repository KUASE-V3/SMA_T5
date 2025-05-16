#include "CertificationCodeFactory.h"

int CertificationCodeFactory::prepaymentQuantity = 0;

int CertificationCodeFactory::createCertificationCode() {
  prepaymentQuantity++;
  prepaymentQuantity %= 1000;
  return 5000 + prepaymentQuantity;
}
