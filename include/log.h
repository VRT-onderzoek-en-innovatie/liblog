#ifndef __LIBLOG_LOG_H__
#define __LIBLOG_LOG_H__

#include "loglevel.h"

/* If the log-level is not specified,
   compile in all */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_TRACE
#endif



#if LOG_LEVEL <= LOG_LEVEL_TRACE
#define LogTrace(fmt, ...) printf(fmt, ## __VA_ARGS__)
#else
#define LogTrace /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LogDebug(fmt, ...) printf(fmt, ## __VA_ARGS__)
#else
#define LogDebug /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LogInfo(fmt, ...)  printf(fmt, ## __VA_ARGS__)
#else
#define LogInfo  /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LogWarn(fmt, ...)  printf(fmt, ## __VA_ARGS__)
#else
#define LogWarn  /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LogError(fmt, ...) printf(fmt, ## __VA_ARGS__)
#else
#define LogError /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_FATAL
#define LogFatal(fmt, ...) printf(fmt, ## __VA_ARGS__)
#else
#define LogFatal /* no-op */
#endif

#endif // defined __LIBLOG_LOG_H__
