#pragma once

#include <string>

class CertificationCodeFactory {
    private:
     static int prepaymentQuantity;
     static const std::string base62;

     std::string toBase62(int num) const ;
     CertificationCodeFactory() = default;
     CertificationCodeFactory(const CertificationCodeFactory&) = delete;
     CertificationCodeFactory& operator=(const CertificationCodeFactory&) = delete;

    public:
     static CertificationCodeFactory& getInstance();
     std::string createCertificationCode() const;
};