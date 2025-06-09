#include "CLManager.h"
#include "CardPay.h"
#include "CertificationCodeFactory.h"
#include "MessageFactory.h"
#include "NetworkManager.h"
#include <iostream>
#include <limits>

int CLManager::readInt(std::string text) {
    while (true) {
        std::cout << text;
        std::string line;
        std::getline(std::cin >> std::ws, line); // 줄 전체 입력 (앞 공백 제거)

        std::istringstream iss(line);
        int value;
        std::string extra;
        if (iss >> value && !(iss >> extra)) {
            return value; // 오직 하나의 숫자만 있을 때
        }
        std::cout << "유효하지 않은 입력입니다.\n";
    }
}

std::string CLManager::readString(std::string text) {
    while (true) {
        std::cout << text;
        std::string line;
        std::getline(std::cin >> std::ws, line); // 앞 공백 제거 후 전체 입력

        // 공백이 포함되어 있으면 잘못된 입력
        if (!line.empty() && line.find(' ') == std::string::npos) {
            return line;
        }

        std::cout << "유효하지 않은 입력입니다. 공백 없는 문자열을 입력하세요.\n";
    }
}

CLManager::CLManager() {
    itemManager = &ItemManager::getInstance();
    prepaymentStock = &PrepaymentStock::getInstance();
    messageFactory = &MessageFactory::getInstance();
    networkManager = &NetworkManager::getInstance();
    certificationCodeFactory = &CertificationCodeFactory::getInstance();
}

CLManager &CLManager::getInstance() {
    static CLManager instance;
    return instance;
}

void CLManager::run() {
    const std::string mainMenuText =
        "메뉴 선택\n1.음료 목록\n2.음료 주문\n3.선결제 코드 확인\n0.종료\n";

    while (true) {
        std::cout << mainMenuText;
        int select = readInt("메뉴 입력: ");
        if (select == 0) return;

        handleMenu(select);
        dvmNavigator.reset();
    }
}

void CLManager::handleMenu(int select) {
    switch (select) {
    case 1:
        showItems();
        break;
    case 2:
        processOrder();
        break;
    case 3:
        checkPrepaymentCode();
        break;
    default:
        std::cout << "존재하지 않는 메뉴 입니다.\n";
        break;
    }
}

void CLManager::processOrder() {
    std::cout << "2.음료 주문\n";

    int itemCode = promptValidItemCode();
    int quantity = promptValidQuantity(itemCode);
    std::string card = readString("카드 정보: ");
    auto method = std::make_unique<CardPay>(card);
    auto payment = std::make_unique<Payment>(itemCode, quantity, std::move(method));

    dvmNavigator = std::make_unique<std::set<Dvm>>();
    networkManager->setDvmNavigator(dvmNavigator.get());

    switch (order(payment)) {
    case ORDER_STATUS::LOCAL:
        handleLocalPayment(std::move(payment));
        break;
    case ORDER_STATUS::REMOTE:
        handleRemotePayment(std::move(payment));
        break;
    case ORDER_STATUS::FAIL:
        std::cout << "음료 주문 불가\n";
        break;
    }
}

int CLManager::promptValidItemCode() {
    while (true) {
        int code = readInt("음료 코드: ");
        auto temp = std::make_unique<Payment>(code);
        if (temp->validate()) return code;
        std::cout << "범위 밖 입력입니다.\n";
    }
}

int CLManager::promptValidQuantity(int itemCode) {
    while (true) {
        int qty = readInt("개수 : ");
        auto temp = std::make_unique<Payment>(itemCode, qty);
        if (temp->validate()) return qty;
        std::cout << "범위 밖 입력입니다.\n";
    }
}

void CLManager::handleLocalPayment(std::unique_ptr<Payment> payment) {
    if (!pay(payment)) {
        std::cout << "결제 실패\n";
        return;
    }

    int itemCode = payment->getItemCode().value();
    int quantity = payment->getQuantity().value();
    if (itemManager->decreaseStock(itemCode, quantity)) {
        std::cout << "음료 제공: " << itemManager->getName(itemCode) << " " << quantity << "개\n";
    } else {
        std::cout << "음료 제공 실패\n";
    }
}

void CLManager::handleRemotePayment(std::unique_ptr<Payment> payment) {
    std::cout << "선결제 하시겠습니까?\n1. 네\n2. 아니오\n";
    int input = readInt("입력: ");
    if (input == 1) {
        auto result = prePay(payment);
        if (result.has_value()) {
            const Dvm &dvm = result->get();
            std::cout << "가장 가까운 자판기 좌표는 (" << dvm.x << ", " << dvm.y << ")입니다.\n"
                      << "인증 코드는 " << payment->getCertCode() << "입니다.\n";
        } else {
            std::cout << "선결제 실패\n";
        }
    } else if (input == 2) {
        std::cout << "가장 가까운 자판기 좌표는 (" << dvmNavigator->begin()->x << ", "
                  << dvmNavigator->begin()->y << ")입니다.\n";
    } else {
        std::cout << "존재하지 않는 메뉴 입니다.\n";
    }
}

void CLManager::checkPrepaymentCode() {
    std::string certCode = readString("선결제 코드 입력: ");
    auto payment = enterCertCode(certCode);
    if (payment.has_value()) {
        int itemCode = payment.value().getItemCode().value();
        int quantity = payment.value().getQuantity().value();
        std::cout << "음료 제공: " << itemManager->getName(itemCode) << " " << quantity << "개\n";
    } else {
        std::cout << "음료 제공 실패\n";
    }
}

void CLManager::showItems() {
    auto items = itemManager->getItems();
    for (const auto &item : items) {
        std::cout << item.toString() << '\n';
    }
}

std::optional<std::reference_wrapper<const Dvm>>
CLManager::prePay(std::unique_ptr<Payment> &payment) {
    // 결제 성공 시
    if (!pay(payment)) {
        return nullopt;
    }

    string certCode = certificationCodeFactory->createCertificationCode();

    payment->setCertCode(certCode);

    int itemCode = payment->getItemCode().value();
    int quantity = payment->getQuantity().value();

    for (const Dvm &dvm : *dvmNavigator) {
        std::string requestMessage =
            messageFactory->createRequestPrepayJson(dvm.id, itemCode, quantity, certCode);

        std::string responseMessage = networkManager->sendMessage(requestMessage);

        json responseJson = json::parse(responseMessage);
        if (responseJson["msg_content"]["availability"]) {
            return dvm;
        }
    }
    return nullopt;
}

ORDER_STATUS CLManager::order(std::unique_ptr<Payment> &payment) {
    if (payment->canLocalBuy()) {
        return ORDER_STATUS::LOCAL;
    } else if (payment->canRemoteBuy()) {
        return ORDER_STATUS::REMOTE;
    } else {
        return ORDER_STATUS::FAIL;
    }
}

bool CLManager::pay(std::unique_ptr<Payment> &payment) {
    return payment->pay();
}

optional<Payment> CLManager::enterCertCode(string certCode) {
    return prepaymentStock->findPaymentBycertCode(certCode);
}