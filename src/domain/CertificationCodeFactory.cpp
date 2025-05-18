#include "CertificationCodeFactory.h"


// TODO: 인증 코드 대소문자+숫자 5자리 문자열

CertificationCodeFactory::CertificationCodeFactory() {

};

CertificationCodeFactory& CertificationCodeFactory::getInstance() {
  static CertificationCodeFactory instance;
  return instance;
}

int CertificationCodeFactory::prepaymentQuantity = 0;

int CertificationCodeFactory::createCertificationCode() {
  prepaymentQuantity++;
  prepaymentQuantity %= 1000;
  return 5000 + prepaymentQuantity;
}
