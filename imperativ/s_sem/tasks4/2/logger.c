#include "logger.h"
#include <stdarg.h>
#include <stdio.h>

static FILE* log_file = NULL;
static int count = 0;

void logSetFile(FILE *file) {
    log_file = file;
}

void logPrintf(const char *format, ...) {
    if (log_file == NULL) {
        return;
    }

    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);

    count++;
}

int getLogCallsCount() {
    return count;
}