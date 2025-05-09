#pragma once

#include <cstdarg>
#include <iostream>

// The attribute tells the compiler to treat `fmt` like a printf format string
void log_info(const char *fmt, const char *file, uint32_t lineNumber, ...) __attribute__((format(printf, 1, 4)));
void log_error(const char *fmt, const char *file, uint32_t lineNumber, ...) __attribute__((format(printf, 1, 4)));

constexpr const char* file_name_only(const char* path) {
    const char* last = path;
    for (const char* p = path; *p != '\0'; ++p) {
        if (*p == '/' || *p == '\\') {
            last = p + 1;
        }
    }
    return last;
}

#define LOG_INFO(str, ...) do { log_info(str, file_name_only(__FILE__), __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_ERROR(str, ...) do { log_info(str, file_name_only(__FILE__), __LINE__, ##__VA_ARGS__); } while(0)
