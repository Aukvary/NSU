#ifndef CREDIT_ACCOUNT_P_H
#define CREDIT_ACCOUNT_P_H

#include "bank_account.h"

#ifdef __cplusplus
extern "C" {
#endif

// Приватная структура кредитового счёта (наследование)
typedef struct {
    bank_account_t base;       // Базовый счёт
    double credit_limit;       // Кредитный лимит
} credit_account_t;

// Приватные функции для кредитового счёта (объявления)
void credit_deposit(bank_account_t* acc, double amount);
int credit_withdraw(bank_account_t* acc, double amount);
double credit_get_balance(bank_account_t* acc);
const char* credit_get_type(bank_account_t* acc);

// Таблица виртуальных функций для кредитового счёта (объявление extern)
extern bank_account_vtable_t credit_vtable;

#ifdef __cplusplus
}
#endif

#endif // CREDIT_ACCOUNT_P_H
