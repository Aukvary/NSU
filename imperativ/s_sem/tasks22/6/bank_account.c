#include "bank_account.h"
#include <stdlib.h>

void destroy_account(bank_account_t* acc) {
    if (acc != NULL) {
        free(acc);
    }
}

void bank_account_deposit(bank_account_t* acc, double amount) {
    if (acc != NULL && acc->vtable != NULL && acc->vtable->deposit != NULL) {
        acc->vtable->deposit(acc, amount);
    }
}

int bank_account_withdraw(bank_account_t* acc, double amount) {
    if (acc == NULL || acc->vtable == NULL || acc->vtable->withdraw == NULL) {
        return 0;
    }
    return acc->vtable->withdraw(acc, amount);
}

double bank_account_get_balance(bank_account_t* acc) {
    if (acc == NULL || acc->vtable == NULL || acc->vtable->get_balance == NULL) {
        return 0.0;
    }
    return acc->vtable->get_balance(acc);
}

const char* bank_account_get_type(bank_account_t* acc) {
    if (acc == NULL || acc->vtable == NULL || acc->vtable->get_type == NULL) {
        return "Unknown";
    }
    return acc->vtable->get_type(acc);
}