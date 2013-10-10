#include "../config.h"

#include "../include/libsimplelog.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

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


const char *LogLevelName[] = {
	"trace",
	"debug",
	"info",
	"warn",
	"error",
	"fatal"
	};
#define LOG_LEVEL_NAME_MAX_LENGTH 5


static struct Log_logger default_logger = {0, "", uninitialized, 0};

static void init_default_logger() {
	if( default_logger.current_log_destination != uninitialized ) return;

	default_logger.current_log_level = 0;
	default_logger.current_log_destination = FileStream;
	default_logger.log_destination_file_stream = stderr;
}

struct Log_logger *LogInit() {
	struct Log_logger *l = malloc(sizeof(struct Log_logger));
	if( l == NULL ) return NULL;
	l->current_log_level = 0;
	l->current_log_destination = Null;
	return l;
}

void LogDeinit(struct Log_logger *l) {
	l->current_log_destination = uninitialized;
	free(l);
}


void LogSetOutputFile(struct Log_logger *l, FILE *out) {
	if( l == NULL ) {
		init_default_logger();
		l = &default_logger;
	}
	l->current_log_destination = FileStream;
	l->log_destination_file_stream = out;
}
FILE *LogGetOutputFile(struct Log_logger *l) {
	if( l == NULL ) {
		init_default_logger();
		l = &default_logger;
	}
	if( l->current_log_destination != FileStream ) return NULL;
	return l->log_destination_file_stream;
}


enum LogLevel LogSetLevel(struct Log_logger *l, enum LogLevel level) {
	enum LogLevel old;
	if( l == NULL ) {
		init_default_logger();
		l = &default_logger;
	}
	old = l->current_log_level;
	l->current_log_level = level;
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

static void output(struct Log_logger *l, char *log_line) {
	char date_str[32];

	switch( l->current_log_destination ) {
	case FileStream:
		genTimestamp(date_str);
		fprintf(l->log_destination_file_stream, "%s %s\n", date_str, log_line);
		break;

	default:
		break;
	}
}

int LogAtLevel_debug(struct Log_logger *l,
                     enum LogLevel level,
                     const char *file, const char *func, const int lineNum,
                     const char *fmt, ...) {
	va_list ap;
	int rv;
	char *buf;
	size_t buf_len;

	if( l == NULL ) {
		init_default_logger();
		l = &default_logger;
	}

	if (level < l->current_log_level) return 0;
	if (l->current_log_destination == Null ) return 0;

	buf = l->buffer; buf_len = sizeof(l->buffer);
	rv = snprintf(buf, buf_len, "[%s from %s:%d (%s)] ",
	              LogLevelName[level],
	              file, lineNum, func);
	if( rv == -1 ) {
		return -1;
	}
	buf += rv; buf_len -= rv;

	va_start(ap,fmt);
	rv = vsnprintf(buf, buf_len, fmt, ap);
	va_end(ap);
	buf += rv; buf_len -= rv;

	output(l, l->buffer);

	return buf - l->buffer;
}

int LogAtLevel_nodebug(struct Log_logger *l,
                       enum LogLevel level,
                       const char *fmt, ...) {
	va_list ap;
	int rv;
	char *buf;
	size_t buf_len;

	if( l == NULL ) {
		init_default_logger();
		l = &default_logger;
	}

	if (level < l->current_log_level) return 0;
	if (l->current_log_destination == Null ) return 0;

	buf = l->buffer; buf_len = sizeof(l->buffer);

	va_start(ap,fmt);
	rv = vsnprintf(buf, buf_len, fmt, ap);
	va_end(ap);
	buf += rv; buf_len -= rv;

	output(l, l->buffer);

	return buf - l->buffer;
}
