#ifndef METHODS_H
#define METHODS_H

#include <sys/types.h>

#define IOIN 0
#define IOOUT 1
#define IOERR 2


void printSecondHalfPrintFirstHalf (const int);
off_t getFileSize(const int);
int writeFromBuffer(const int, const char*, size_t);

#endif //METHODS_H