#pragma once

class CertificationCodeFactory {
    private:
     static int prepaymentQuantity;

     CertificationCodeFactory();
     CertificationCodeFactory(const CertificationCodeFactory&) = delete;
     CertificationCodeFactory& operator=(const CertificationCodeFactory&) = delete;

    public:
     static CertificationCodeFactory& getInstance();
     int createCertificationCode();
};