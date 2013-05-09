#include "../include/log.h"
#include <stdio.h>
#include <stdarg.h>

static enum LogLevel current_log_level = Trace;

int LogAtLevel(enum LogLevel level,
               const char *file, const char *func, const int lineNum,
               const char *fmt, ...) {
	va_list ap;
	int rv;

	if( level < current_log_level ) return 0;

	fprintf(stdout, "%s: ", LogLevelName[level]);
	fprintf(stdout, "from %s:%d (%s): ", file, lineNum, func);
	va_start(ap,fmt);
	rv = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return rv;
}
