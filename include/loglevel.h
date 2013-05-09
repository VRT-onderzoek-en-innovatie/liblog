#ifndef __LIBLOG_LOGLEVEL_H__
#define __LIBLOG_LOGLEVEL_H__

#define LOG_LEVEL_TRACE 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO  2
#define LOG_LEVEL_WARN  3
#define LOG_LEVEL_ERROR 4
#define LOG_LEVEL_FATAL 5

typedef enum LogLevel {
	Trace=0,
	Debug,
	Info,
	Warn,
	Error,
	Fatal
	} LogLevel;

const char *LogLevelName[] = {
	"trace",
	"debug",
	"info",
	"warn",
	"error",
	"fatal"
	};
#define LOG_LEVEL_NAME_MAX_LENGTH 5

#endif // defined __LIBLOG_LOGLEVEL_H__
