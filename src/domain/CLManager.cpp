#include "CLManager.h"
#include "CertificationCodeFactory.h"
#include "MessageFactory.h"
#include <iostream>

using namespace std;

void CLManager::showItems() {
    auto items = itemManager.getItems();
    for (const auto &item : items) {
        std::cout << item.toString() << '\n';
    }
}

void CLManager::prePay(Payment& payment){

    // 결제 성공 시

    int certCode = CertificationCodeFactory::createCertificationCode();

    // payment.setCertCode(certCode);

    // TODO: getItems
    string message = MessageFactory::createRequestStockJson(3, 4);

    // request 전송

    // response 대기

    // T F 따라서 반환값 다르게 또는 payment 값세팅

}