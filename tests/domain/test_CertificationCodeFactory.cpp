#include <gtest/gtest.h>

#include "CertificationCodeFactory.h"
#include "Dvm.h"
#include <cmath>

TEST(CertificationCodeFactoryTest, CreateCertificationCode) {
    CertificationCodeFactory &certificationCodeFactory = CertificationCodeFactory::getInstance();
    Dvm::vmId = 5;
    std::string certCode1 = certificationCodeFactory.createCertificationCode();
    std::string certCode2 = certificationCodeFactory.createCertificationCode();

    int cycle = pow(62, 4);

    for (int i = 0; i < cycle; i++) {
      certificationCodeFactory.createCertificationCode();
    }

  std::string certCode3 = certificationCodeFactory.createCertificationCode();

  EXPECT_EQ(certCode1, "5AAAA");
  EXPECT_EQ(certCode2, "5AAAB");
  EXPECT_EQ(certCode3, "5AAAC");

};