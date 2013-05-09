#ifndef __LIBLOG_LOG_H__
#define __LIBLOG_LOG_H__

#include "liblog_level.h"
#include <stdio.h>

/* If the log-level is not specified,
   compile in all */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_TRACE
#endif

int LogAtLevel(enum LogLevel level,
               const char *file, const char *func, const int lineNum,
               const char *fmt, ...);

enum LogLevel LogSetLevel(enum LogLevel level);
FILE *LogSetOutput(FILE *out);

#if LOG_LEVEL <= LOG_LEVEL_TRACE
#define LogTrace(fmt, ...) LogAtLevel(Trace, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogTrace /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LogDebug(fmt, ...) LogAtLevel(Debug, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogDebug /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LogInfo(fmt, ...)  LogAtLevel(Info, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogInfo  /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LogWarn(fmt, ...)  LogAtLevel(Warn, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogWarn  /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LogError(fmt, ...) LogAtLevel(Error, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogError /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_FATAL
#define LogFatal(fmt, ...) LogAtLevel(Fatal, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogFatal /* no-op */
#endif

#endif // defined __LIBLOG_LOG_H__
