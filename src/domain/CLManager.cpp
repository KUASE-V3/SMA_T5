#include "CLManager.h"
#include "CertificationCodeFactory.h"
#include "MessageFactory.h"
#include "CardPay.h"
#include "NetworkManager.h"
#include <iostream>
#include <limits>

int CLManager::readInt(std::string text) {
    int input;
    std::cout << text;
    while (!(std::cin >> input)) {
        std::cout << "유효하지 않은 입력입니다. 다시 입력하세요: ";
        std::cin.clear(); // 오류 상태 플래그 초기화
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 잘못된 입력 무시
        std::cout << text;
    }
    return input;
}

CLManager::CLManager() {}

CLManager &CLManager::getInstance() {
    static CLManager instance;
    return instance;
}

void CLManager::run() {
    std::string mainMenuText = "메뉴 선택\n1.음료 목록\n2.음료 주문\n3.선결제 코드 확인\n0.종료\n";
    std::string listMenutext = "1.음료 목록\n";
    std::string orderMenuText = "2.음료 주문\n";
    std::string invalidMenuMsg = "존재하지 않는 메뉴 입니다.";
    std::string orderFailMsg = "음료 주문 불가";

    while (true) {
        std::cout << mainMenuText;
        int select = readInt("입력: ");
        if (select == 0) {
            return;
        } else if (select == 1) {
            std::cout << listMenutext;
            showItems();
        } else if (select == 2) {
            std::cout << orderMenuText;
            int itemCode = readInt("음료 코드: ");
            int quantity = readInt("개수 : ");
            std::cout << "카드 정보: ";
            std::string card;
            std::cin >> card;
            ORDER_STATUS status = order(itemCode, quantity, card);

            if (status == ORDER_STATUS::LOCAL) {
                // todo : pay();
            } else if (status == ORDER_STATUS::REMOTE) {
                // todo : prePay();
            } else if (status == ORDER_STATUS::FAIL) {
                std::cout << orderFailMsg;
            }
        } else if (select == 3) {
            // todo : check cert
        } else {
            std::cout << invalidMenuMsg << std::endl;
        }
    }
}


void CLManager::showItems() {
    auto items = itemManager.getItems();
    for (const auto &item : items) {
        std::cout << item.toString() << '\n';
    }
}

void CLManager::prePay(Payment& payment){

    // 결제 성공 시

    int certCode = CertificationCodeFactory::createCertificationCode();

    payment.setCertCode(certCode);

    std::pair<int, int> item = payment.getItems();

    // std::string requestMessage = MessageFactory::createRequestPrepayJson(item.first, item.second, certCode);

    // std::string responseMessage = NetworkManager::sendMessage(requestMessage);

    // T F 따라서 반환값 다르게 또는 payment 값세팅

}

ORDER_STATUS CLManager::order(int itemCode, int quantity, std::string card) {
    auto method = std::make_unique<CardPay>(card);
    Payment payment(itemCode, quantity, std::move(method));

    if (payment.canLocalBuy()) {
        return ORDER_STATUS::LOCAL;
    } else if (payment.canRemoteBuy()) {
        return ORDER_STATUS::REMOTE;
    } else {
        return ORDER_STATUS::FAIL;
    }
}
