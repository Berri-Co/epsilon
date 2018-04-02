#include <stdio.h>
#include <stdarg.h>

static void putcp(void* p, char c) {
  *(*((char**)p))++ = c;
}

void vsprintf(char * s, const char * format, va_list arg ) {
  return tfp_format(&s, putcp, format, arg);
}
