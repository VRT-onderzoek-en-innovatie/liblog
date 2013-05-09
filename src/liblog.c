#include "../include/log.h"
#include <stdio.h>
#include <stdarg.h>

static enum LogLevel current_log_level = Trace;

int LogAtLevel(enum LogLevel level, const char *fmt, ...) {
	va_list ap;
	int rv;
	va_start(ap,fmt);
	rv = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return rv;
}
