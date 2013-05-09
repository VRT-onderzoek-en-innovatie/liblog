#ifndef __LIBLOG_LOGLEVEL_H__
#define __LIBLOG_LOGLEVEL_H__

#define LOG_LEVEL_TRACE 1
#define LOG_LEVEL_DEBUG 2
#define LOG_LEVEL_INFO  3
#define LOG_LEVEL_WARN  4
#define LOG_LEVEL_ERROR 5
#define LOG_LEVEL_FATAL 6

typedef enum LogLevel {
	Trace=1,
	Debug,
	Info,
	Warn,
	Error,
	Fatal
	} LogLevel;

#endif // defined __LIBLOG_LOGLEVEL_H__
