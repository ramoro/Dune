#include "cola_cerrada_error.h"
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <string.h>

ColaCerradaError::ColaCerradaError(const char* fmt, ...) 
noexcept {
	va_list args;
	va_start(args, fmt);
	int s = vsnprintf(msg_error, BUF_LONG, fmt, args);
	va_end(args);

	strncpy(msg_error + s, strerror(errno), BUF_LONG - s);
	msg_error[BUF_LONG - 1] = 0;
}

const char* ColaCerradaError::what() const noexcept {
	return msg_error;
}
