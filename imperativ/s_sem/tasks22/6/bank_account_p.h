#ifndef BANK_ACCOUNT_P_H
#define BANK_ACCOUNT_P_H

#include "bank_account.h"

#ifdef __cplusplus
extern "C" {
#endif

// Приватные функции для работы с bank_account (объявления)
// Определения в bank_account_private.c
void bank_account_deposit(bank_account_t* acc, double amount);
int bank_account_withdraw(bank_account_t* acc, double amount);
double bank_account_get_balance(bank_account_t* acc);
const char* bank_account_get_type(bank_account_t* acc);

#ifdef __cplusplus
}
#endif

#endif // BANK_ACCOUNT_P_H
