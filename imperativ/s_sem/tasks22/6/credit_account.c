#include "credit_account.h"
#include "credit_account_p.h"
#include <stdlib.h>

static void credit_deposit_impl(bank_account_t* acc, double amount) {
    if (acc == NULL || amount <= 0) {
        return;
    }
    acc->balance += amount;
}

static int credit_withdraw_impl(bank_account_t* acc, double amount) {
    if (acc == NULL || amount <= 0) {
        return 0;
    }
    
    credit_account_t* credit_acc = (credit_account_t*)acc;
    
    if (credit_acc->credit_limit < 0) {
        return 0;
    }
    
    double min_balance = -credit_acc->credit_limit;
    
    if (acc->balance - amount >= min_balance) {
        acc->balance -= amount;
        return 1;
    }
    return 0;
}

static double credit_get_balance_impl(bank_account_t* acc) {
    if (acc == NULL) {
        return 0.0;
    }
    return acc->balance;
}

static const char* credit_get_type_impl(bank_account_t* acc) {
    (void)acc;
    return "Credit";
}

static bank_account_vtable_t credit_vtable_instance = {
    .deposit = credit_deposit_impl,
    .withdraw = credit_withdraw_impl,
    .get_balance = credit_get_balance_impl,
    .get_type = credit_get_type_impl
};

bank_account_t* create_credit_account(int number, double limit) {
    credit_account_t* acc = (credit_account_t*)malloc(sizeof(credit_account_t));
    if (acc != NULL) {
        acc->base.account_number = number;
        acc->base.balance = 0.0;
        acc->base.vtable = &credit_vtable_instance;
        acc->credit_limit = limit;
    }
    return (bank_account_t*)acc;
}