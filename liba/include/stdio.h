#ifndef LIBA_STDIO_H
#define LIBA_STDIO_H

#include <stddef.h>
#include <stdarg.h>
#include <printf.h>

#define stdin 0
#define stdout 0
#define EOF 0

typedef void FILE;

#define snprintf(s, n, format, ...) sprintf(s, format, __VA_ARGS__)
#define vsnprintf(s, n, format, arg) vsprintf(s, format, arg)

#endif
