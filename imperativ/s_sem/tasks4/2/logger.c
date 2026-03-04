#include "logger.h"

static int count = 0;
static FILE* out;

void logSetFile(FILE *file) {
    if (file) {
        
    } else {
        
    }
}

void logPrintf(const char *format, ...) {
    
}

int getLogCallsCount() {
    return count;
}