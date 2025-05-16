#include <gtest/gtest.h>

#include "CertificationCodeFactory.h"

TEST(CertificationCodeFactoryTest, CreateCertificationCode) {
  int certCode1 = CertificationCodeFactory::createCertificationCode();
  int certCode2 = CertificationCodeFactory::createCertificationCode();

  for (int i = 0; i < 1000; i++) {
    CertificationCodeFactory::createCertificationCode();
  }

  int certCode1003 = CertificationCodeFactory::createCertificationCode();

  EXPECT_EQ(certCode1, 5001);
  EXPECT_EQ(certCode2, 5002);
  EXPECT_EQ(certCode1003, 5003);
};