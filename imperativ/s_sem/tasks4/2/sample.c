#include "logger.h"
#include "pack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main() {
    logPrintf("Not enabled logging yet\n"); //ignored
    logSetFile(stderr);
    logPrintf("Logging in stderr\n");       //goes to stderr
    logSetFile(stdout);
    logPrintf("Logging enabled!\n");        //goes to stdout

    int five = 5, ten = 10;
    double unit = 1.0;
    const char *hello = "hello";

    logPrintf(
        "Quering number of bytes for: [%d] [%lf] [%s] [%d]\n",
        five, unit, hello, ten
    );
    int bytes = pack(NULL, "%d%lf%s%d", five, unit, hello, ten);
    logPrintf("Allocating buffer of size %d\n", bytes);
    char *buffer = malloc(bytes);
    logPrintf("Packing data into buffer\n");
    int written = pack(buffer, "%d%lf%s%d", five, unit, hello, ten);

    logPrintf("Checking result\n");
    assert(written == bytes && written == 22);
    char correct[22] = {                    //note: assume little-endian
        0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
        'h', 'e', 'l', 'l', 'o', 0,
        0x0A, 0x00, 0x00, 0x00
    };
    assert(memcmp(buffer, correct, sizeof(correct)) == 0);

    free(buffer);
    logSetFile(0);
    logPrintf("Sample finished\n");         //ignored

    logSetFile(stdout);
    logPrintf("Sample really finished\n");  //printed

    assert(getLogCallsCount() == 7);
    return 0;
}
