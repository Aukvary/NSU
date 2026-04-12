#ifndef DEBIT_ACCOUNT_P_H
#define DEBIT_ACCOUNT_P_H

#include "bank_account.h"

#ifdef __cplusplus
extern "C" {
#endif

// Приватные функции для дебетового счёта (объявления)
void debit_deposit(bank_account_t* acc, double amount);
int debit_withdraw(bank_account_t* acc, double amount);
double debit_get_balance(bank_account_t* acc);
const char* debit_get_type(bank_account_t* acc);

// Таблица виртуальных функций для дебетового счёта (объявление extern)
extern bank_account_vtable_t debit_vtable;

#ifdef __cplusplus
}
#endif

#endif // DEBIT_ACCOUNT_P_H
