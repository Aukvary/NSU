#include "debit_account.h"
#include "debit_account_p.h"
#include <stdlib.h>

static void debit_deposit_impl(bank_account_t* acc, double amount) {
    if (acc == NULL || amount <= 0) {
        return;
    }
    acc->balance += amount;
}

static int debit_withdraw_impl(bank_account_t* acc, double amount) {
    if (acc == NULL || amount <= 0) {
        return 0;
    }
    if (acc->balance >= amount) {
        acc->balance -= amount;
        return 1;
    }
    return 0;
}

static double debit_get_balance_impl(bank_account_t* acc) {
    if (acc == NULL) {
        return 0.0;
    }
    return acc->balance;
}

static const char* debit_get_type_impl(bank_account_t* acc) {
    (void)acc;
    return "Debit";
}

static bank_account_vtable_t debit_vtable_instance = {
    .deposit = debit_deposit_impl,
    .withdraw = debit_withdraw_impl,
    .get_balance = debit_get_balance_impl,
    .get_type = debit_get_type_impl
};

bank_account_t* create_debit_account(int number) {
    bank_account_t* acc = (bank_account_t*)malloc(sizeof(bank_account_t));
    if (acc != NULL) {
        acc->account_number = number;
        acc->balance = 0.0;
        acc->vtable = &debit_vtable_instance;
    }
    return acc;
}