#ifndef DEBIT_ACCOUNT_H
#define DEBIT_ACCOUNT_H

#include "bank_account.h"

#ifdef __cplusplus
extern "C" {
#endif

// Создание дебетового счёта
bank_account_t* create_debit_account(int number);

#ifdef __cplusplus
}
#endif

#endif // DEBIT_ACCOUNT_H
