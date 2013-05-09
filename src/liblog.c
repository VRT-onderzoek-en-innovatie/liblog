#include "../config.h"

#include "../include/liblog.h"
#include <stdarg.h>
#include <string.h>

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif


static enum LogLevel current_log_level = Trace;
static FILE *output = NULL;

FILE *LogSetOutput(FILE *out) {
	FILE *old = output;
	output = out;
	return old;
}

static void genTimestamp(char *date_str) {
	struct timeval tv_now;
	struct tm *now;

	if( -1 == gettimeofday(&tv_now, NULL) ) {
		strcpy(date_str, "gettimeofday() failed");
		return;
	}

	now = localtime(&tv_now.tv_sec);

	if (0 == strftime(date_str, 20, "%Y-%m-%dT%H:%M:%S", now)) {
		strcpy(date_str, "strftime1() failed");
		return;
	}

	if( 7 != sprintf(date_str+19, ".%06d", tv_now.tv_usec) ) {
		strcpy(date_str, "sprintf() failed");
		return;
	}

	if (0 == strftime(date_str+26, 6, "%z", now)) {
		strcpy(date_str, "strftime2() failed");
		return;
	}
}

int LogAtLevel(enum LogLevel level,
               const char *file, const char *func, const int lineNum,
               const char *fmt, ...) {
	va_list ap;
	int rv;
	char date_str[32];

	if (level < current_log_level) return 0;
	if (output == NULL) LogSetOutput(stdout);

	genTimestamp(date_str);

	fprintf(output, "%s %s from %s:%d (%s): ",
	                date_str, LogLevelName[level],
	                file, lineNum, func);

	va_start(ap,fmt);
	rv = vfprintf(output, fmt, ap);
	va_end(ap);

	fprintf(output, "\n");

	return rv;
}

enum LogLevel LogSetLevel(enum LogLevel level) {
	enum LogLevel old = current_log_level;
	current_log_level = level;
	return old;
}
