#include "CertificationCodeFactory.h"
#include <cmath>

CertificationCodeFactory::CertificationCodeFactory() {

};

string const CertificationCodeFactory::base62 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

string CertificationCodeFactory::toBase62(int num) {
  // 5번 Dvm이 생성하는 코드
  string result;
  for (int i = 0; i < 4; ++i) {
    result = base62[num % 62] + result;
    num /= 62;
  }

  result = "5" + result;
  return result;
}

CertificationCodeFactory& CertificationCodeFactory::getInstance() {
  static CertificationCodeFactory instance;
  return instance;
}

int CertificationCodeFactory::prepaymentQuantity = 0;

string CertificationCodeFactory::createCertificationCode() {
  string certCode = toBase62(prepaymentQuantity);
  prepaymentQuantity++;
  prepaymentQuantity %= (int) pow(62, 4);
  return certCode;
}
