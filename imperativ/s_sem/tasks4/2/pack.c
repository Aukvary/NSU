#include "pack.h"
#include <stdarg.h>
#include <string.h>

int pack(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int bytes = 0;
    const char *fmt = format;

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 'd') {
                int val = va_arg(args, int);
                if (buffer != NULL) {
                    *(int *)(buffer + bytes) = val;
                }
                bytes += 4;
            } else if (*fmt == 'l' && *(fmt + 1) == 'f') {
                fmt++; 
                double val = va_arg(args, double);
                if (buffer != NULL) {
                    *(double *)(buffer + bytes) = val;
                }
                bytes += 8;
            } else if (*fmt == 's') {
                char *str = va_arg(args, char *);
                int len = strlen(str) + 1; 
                if (buffer != NULL) {
                    memcpy(buffer + bytes, str, len);
                }
                bytes += len;
            }
        }
        fmt++;
    }

    va_end(args);
    return bytes;
}