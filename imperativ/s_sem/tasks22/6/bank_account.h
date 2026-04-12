#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // Forward declaration
    typedef struct bank_account bank_account_t;

    // Структура таблицы виртуальных функций (полиморфизм)
    typedef struct
    {
        void (*deposit)(bank_account_t *acc, double amount);
        int (*withdraw)(bank_account_t *acc, double amount);
        double (*get_balance)(bank_account_t *acc);
        const char *(*get_type)(bank_account_t *acc);
    } bank_account_vtable_t;

    // Базовая структура банковского счёта (инкапсуляция)
    struct bank_account
    {
        int account_number;
        double balance;
        bank_account_vtable_t *vtable;
    };

    // Объявления функций (определения в bank_account.c)
    void destroy_account(bank_account_t *acc);

    // Операции над счетами (объявления, определения в bank_account_impl.h)
    void bank_account_deposit(bank_account_t *acc, double amount);
    int bank_account_withdraw(bank_account_t *acc, double amount);
    double bank_account_get_balance(bank_account_t *acc);
    const char *bank_account_get_type(bank_account_t *acc);

#ifdef __cplusplus
}
#endif

#endif // BANK_ACCOUNT_H
