#include <gtest/gtest.h>
#include "bank_account.h"
#include "debit_account.h"
#include "credit_account.h"

TEST(DebitAccountTest, CreateAndDestroy) {
    bank_account_t* acc = create_debit_account(1);
    ASSERT_NE(acc, nullptr);
    destroy_account(acc);
}

TEST(DebitAccountTest, Deposit) {
    bank_account_t* acc = create_debit_account(1);
    bank_account_deposit(acc, 100.0);
    EXPECT_DOUBLE_EQ(bank_account_get_balance(acc), 100.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, WithdrawSuccess) {
    bank_account_t* acc = create_debit_account(1);
    bank_account_deposit(acc, 100.0);
    int result = bank_account_withdraw(acc, 50.0);
    EXPECT_EQ(result, 1);
    EXPECT_DOUBLE_EQ(bank_account_get_balance(acc), 50.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, WithdrawFailInsufficientFunds) {
    bank_account_t* acc = create_debit_account(1);
    bank_account_deposit(acc, 100.0);
    int result = bank_account_withdraw(acc, 150.0);
    EXPECT_EQ(result, 0);
    EXPECT_DOUBLE_EQ(bank_account_get_balance(acc), 100.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, GetType) {
    bank_account_t* acc = create_debit_account(1);
    EXPECT_STREQ(bank_account_get_type(acc), "Debit");
    destroy_account(acc);
}

TEST(CreditAccountTest, CreateAndDestroy) {
    bank_account_t* acc = create_credit_account(1, 500.0);
    ASSERT_NE(acc, nullptr);
    destroy_account(acc);
}

TEST(CreditAccountTest, DepositPositive) {
    bank_account_t* acc = create_credit_account(1, 500.0);
    bank_account_deposit(acc, 100.0);
    EXPECT_DOUBLE_EQ(bank_account_get_balance(acc), 100.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, WithdrawWithinLimit) {
    bank_account_t* acc = create_credit_account(1, 500.0);
    int result = bank_account_withdraw(acc, 300.0);
    EXPECT_EQ(result, 1);
    EXPECT_DOUBLE_EQ(bank_account_get_balance(acc), -300.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, WithdrawExceedsLimit) {
    bank_account_t* acc = create_credit_account(1, 500.0);
    int result = bank_account_withdraw(acc, 600.0);
    EXPECT_EQ(result, 0);
    EXPECT_DOUBLE_EQ(bank_account_get_balance(acc), 0.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, WithdrawWithZeroLimit) {
    bank_account_t* acc = create_credit_account(1, 0.0);
    bank_account_deposit(acc, 100.0);
    int result = bank_account_withdraw(acc, 150.0);
    EXPECT_EQ(result, 0);
    EXPECT_DOUBLE_EQ(bank_account_get_balance(acc), 100.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, WithdrawWithNegativeLimit) {
    bank_account_t* acc = create_credit_account(1, -100.0);
    int result = bank_account_withdraw(acc, 50.0);
    EXPECT_EQ(result, 0);
    EXPECT_DOUBLE_EQ(bank_account_get_balance(acc), 0.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, GetType) {
    bank_account_t* acc = create_credit_account(1, 500.0);
    EXPECT_STREQ(bank_account_get_type(acc), "Credit");
    destroy_account(acc);
}

TEST(NullHandlingTest, DestroyNull) {
    destroy_account(nullptr);
}

TEST(NullHandlingTest, DepositNull) {
    bank_account_deposit(nullptr, 100.0);
}

TEST(NullHandlingTest, WithdrawNull) {
    int result = bank_account_withdraw(nullptr, 100.0);
    EXPECT_EQ(result, 0);
}

TEST(NullHandlingTest, GetBalanceNull) {
    double balance = bank_account_get_balance(nullptr);
    EXPECT_DOUBLE_EQ(balance, 0.0);
}

TEST(NullHandlingTest, GetTypeNull) {
    const char* type = bank_account_get_type(nullptr);
    EXPECT_STREQ(type, "Unknown");
}