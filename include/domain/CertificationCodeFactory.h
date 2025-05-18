#pragma once

#include <string>

using namespace std;

class CertificationCodeFactory {
    private:
     static int prepaymentQuantity;
     static const string base62;

     string toBase62(int num);
     CertificationCodeFactory();
     CertificationCodeFactory(const CertificationCodeFactory&) = delete;
     CertificationCodeFactory& operator=(const CertificationCodeFactory&) = delete;

    public:
     static CertificationCodeFactory& getInstance();
     string createCertificationCode();
};