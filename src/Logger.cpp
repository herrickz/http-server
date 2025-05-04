
#include "Logger.h"

void log_info(const char *fmt, const char *file, uint32_t lineNumber, ...) {
    va_list args;
    va_start(args, lineNumber);
    printf("[INFO] %s: %d ", file, lineNumber);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

void log_error(const char *fmt, const char *file, uint32_t lineNumber, ...) {
    va_list args;
    va_start(args, lineNumber);
    printf("[ERROR] %s: %d ", file, lineNumber);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}