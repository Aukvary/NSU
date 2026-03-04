#ifndef PACK_9835644534983774
#define PACK_9835644534983774

// Packs specified arguments into specified "buffer" as binary data.
//
// The arguments are passed in printf-like fashion.
// Format string consists only of the following pieces:
//   %d  --- next argument is signed 32-bit int
//   %lf --- next argument is 64-bit floating point number
//   %s  --- next argument is null-terminated string
//
// All the arguments are copied into buffer in the correct order.
// For %d and %lf, 4 and 8 bytes respectively are copied into the buffer.
// For %s, the whole string including null-terminated byte is copied into buffer.
//
// The return value is the total number of bytes written to the buffer.
// Since caller does not know how long the buffer should be, two modes are supported:
//   1. If buffer == 0, only return the number of bytes, don't write anything.
//   2. If buffer != 0, write data into the buffer and return the number of bytes written.

int pack(char *buffer, const char *format, ...);

#endif
