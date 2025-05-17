#include <gtest/gtest.h>
#include "ValidatorFactory.h"
#include "LocalItemValidateAdapter.h"
#include "RemoteItemValidateAdapter.h"
#include "CardPayValidateAdapter.h"

TEST(ValidatorFactoryTest, AllValidatorsAreRegistered) {
    ValidatorFactory& factory = ValidatorFactory::getInstance();
    auto map = factory.setValidatorList();

    // map 크기 검사
    EXPECT_EQ(map.size(), 3);

    // 각 Validator가 포함되어 있고 nullptr이 아님
    EXPECT_TRUE(map.count(typeid(LocalItemValidateAdapter)));
    EXPECT_TRUE(map.count(typeid(RemoteItemValidateAdapter)));
    EXPECT_TRUE(map.count(typeid(CardPayValidateAdapter)));

    EXPECT_NE(map[typeid(LocalItemValidateAdapter)], nullptr);
    EXPECT_NE(map[typeid(RemoteItemValidateAdapter)], nullptr);
    EXPECT_NE(map[typeid(CardPayValidateAdapter)], nullptr);
}

TEST(ValidatorFactoryTest, ValidatorsHaveCorrectRuntimeType) {
    ValidatorFactory& factory = ValidatorFactory::getInstance();
    auto map = factory.setValidatorList();

    EXPECT_TRUE(dynamic_cast<LocalItemValidateAdapter*>(map[typeid(LocalItemValidateAdapter)].get()) != nullptr);
    EXPECT_TRUE(dynamic_cast<RemoteItemValidateAdapter*>(map[typeid(RemoteItemValidateAdapter)].get()) != nullptr);
    EXPECT_TRUE(dynamic_cast<CardPayValidateAdapter*>(map[typeid(CardPayValidateAdapter)].get()) != nullptr);
}
