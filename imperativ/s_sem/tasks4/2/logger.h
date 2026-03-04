#ifndef LOGGER_195137346889621
#define LOGGER_195137346889621

#include <stdio.h>

// If file != 0, then enables logging and sets current logfile.
// All the messages printed by logPrintf go into this file afterwards.
// If file = 0, disables logging (logPrintf does nothing afterwards).
// Logging is also disabled initially.
// The file is NOT closed when logging is disabled.
void logSetFile(FILE *file);

// Prints text message to the current logfile (with printf formatting).
// If logging is disabled, then it does nothing.
void logPrintf(const char *format, ...);

// Returns the number of successful logPrintf calls since program start.
// A call is considered unsuccessful when logging is disabled.
int getLogCallsCount();

#endif
