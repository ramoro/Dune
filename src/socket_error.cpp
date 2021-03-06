#include "socket_error.h"
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <string.h>

SocketError::SocketError(const char* fmt, ...) 
noexcept {
	va_list args;
	va_start(args, fmt);
	int s = vsnprintf(msg_error, BUF_LEN, fmt, args);
	va_end(args);

	strncpy(msg_error + s, strerror(errno), BUF_LEN - s);
	msg_error[BUF_LEN - 1] = 0;
}

const char* SocketError::what() const noexcept {
	return msg_error;
}
