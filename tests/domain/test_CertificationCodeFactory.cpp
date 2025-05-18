#include <gtest/gtest.h>

#include "CertificationCodeFactory.h"

TEST(CertificationCodeFactoryTest, CreateCertificationCode) {
    CertificationCodeFactory &certificationCodeFactory = CertificationCodeFactory::getInstance();
  int certCode1 = certificationCodeFactory.createCertificationCode();
  int certCode2 = certificationCodeFactory.createCertificationCode();

  for (int i = 0; i < 1000; i++) {
    certificationCodeFactory.createCertificationCode();
  }

  int certCode1003 = certificationCodeFactory.createCertificationCode();

  EXPECT_EQ(certCode1, 5001);
  EXPECT_EQ(certCode2, 5002);
  EXPECT_EQ(certCode1003, 5003);
};