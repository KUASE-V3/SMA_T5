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
            std::unique_ptr<Payment> payment;

            dvmNavigator = std::make_unique<std::set<Dvm>>();
            networkManager->setDvmNavigator(dvmNavigator.get());

            ORDER_STATUS status = order(itemCode, quantity, card, payment);

            if (status == ORDER_STATUS::LOCAL) {
                if (pay(payment)) {
                    std::pair<int, int> items = payment->getOrder();
                    int itemCode = items.first;
                    int quantity = items.second;
                    if (itemManager->decreaseStock(itemCode, quantity)) {
                        std::string itemName = itemManager->getName(itemCode);
                        std::cout << "음료 제공: " << itemName << " " << quantity << "개\n";
                    } else {
                        std::cout << "음료 제공 실패";
                    }
                }
            } else if (status == ORDER_STATUS::REMOTE) {
              auto result = prePay(payment);
              if (result.has_value()) {
                const Dvm &dvm = result->get();
              } else {
                // 선결제 실패 재고 없어서 or 통신 실패
              }
            } else if (status == ORDER_STATUS::FAIL) {
                std::cout << orderFailMsg;
            }
        } else if (select == 3) {
            // TODO 사용자로부터 certCode 입력받고
            // if(enterCertCode().has_value()) {

            // }else {

            // }

        } else {
            std::cout << invalidMenuMsg << std::endl;
        }
        dvmNavigator.reset();
    }
}


void CLManager::showItems() {
    auto items = itemManager->getItems();
    for (const auto &item : items) {
        std::cout << item.toString() << '\n';
    }
}

std::optional < std::reference_wrapper<const Dvm>> CLManager::prePay(
                    std::unique_ptr<Payment> &payment) {
  // 결제 성공 시
  if(!pay(payment)) {
    return nullopt;
  }

  int certCode = certificationCodeFactory->createCertificationCode();

  payment->setCertCode(certCode);

  std::pair<int, int> item = payment->getOrder();

  for (const Dvm &dvm : *dvmNavigator) {
    std::string requestMessage = messageFactory->createRequestPrepayJson(
        dvm.id, item.first, item.second, certCode);

    std::string responseMessage = networkManager->sendMessage(requestMessage);

    json responseJson = json::parse(responseMessage);
    if (responseJson["msg_content"]["availability"]) {
      return dvm;
    }
  }
  return nullopt;
}

ORDER_STATUS CLManager::order(int itemCode, int quantity, const std::string &card,
                              std::unique_ptr<Payment> &payment) {
    auto method = std::make_unique<CardPay>(card);
    payment = std::make_unique<Payment>(itemCode, quantity, std::move(method));

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

optional<Payment> CLManager::enterCertCode(int certCode) {
    return prepaymentStock->findPaymentBycertCode(certCode);
}
