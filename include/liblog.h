#ifndef __LIBLOG_LOG_H__
#define __LIBLOG_LOG_H__

#include "liblog_level.h"
#include <stdio.h>

/* If the log-level is not specified,
   compile in all */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_TRACE
#endif

#define LOG_MAX_LINE_LENGTH 4096

#ifdef __cplusplus
extern "C"{
#endif

enum LogDestination {
	Null,
	FileStream,
	uninitialized
	};

struct Log_logger {
	enum LogLevel current_log_level;
	char buffer[LOG_MAX_LINE_LENGTH];
	enum LogDestination current_log_destination;
	FILE *log_destination_file_stream;
};


/* Initialize a new logger
 * Returns NULL on failure
 */
struct Log_logger *Log_init();

/* Terminate a logger. All resources are free'd
 */
void Log_deinit(struct Log_logger *l);


/* Set the run-time log level.
 * Log messages below this level will not produce output
 *
 * It is meaningless to set this to a level below the LOG_LEVEL used to compile
 * the binary with, since these Log-statements are not compiled in.
 */
enum LogLevel LogSetLevel(struct Log_logger *l, enum LogLevel level);


/* Start logging to the file specified.
 */
void LogSetOutputFile(struct Log_logger *l, FILE *out);
/* Get the current output file, or NULL if not logging to file
 */
FILE *LogGetOutputFile(struct Log_logger *l);



/* Helper function for the Log{Level} macro's */
int LogAtLevel_debug(struct Log_logger *l,
                     enum LogLevel level,
                     const char *file, const char *func, const int lineNum,
                     const char *fmt, ...);
int LogAtLevel_nodebug(struct Log_logger *l,
                       enum LogLevel level,
                       const char *fmt, ...);

#ifdef __cplusplus
}
#endif


#if LOG_LEVEL <= LOG_LEVEL_TRACE
#ifdef DEBUG
#define LogTrace(fmt, ...)               LogAtLevel_debug(NULL,   Trace, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#define LogLoggerTrace(logger, fmt, ...) LogAtLevel_debug(logger, Trace, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogTrace(fmt, ...)               LogAtLevel_nodebug(NULL,   Trace, fmt, ## __VA_ARGS__)
#define LogLoggerTrace(logger, fmt, ...) LogAtLevel_nodebug(logger, Trace, fmt, ## __VA_ARGS__)
#endif
#else
#define LogTrace       /* no-op */
#define LogLoggerTrace /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#ifdef DEBUG
#define LogDebug(fmt, ...)               LogAtLevel_debug(NULL,   Debug, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#define LogLoggerDebug(logger, fmt, ...) LogAtLevel_debug(logger, Debug, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogDebug(fmt, ...)               LogAtLevel_nodebug(NULL,   Debug, fmt, ## __VA_ARGS__)
#define LogLoggerDebug(logger, fmt, ...) LogAtLevel_nodebug(logger, Debug, fmt, ## __VA_ARGS__)
#endif
#else
#define LogDebug       /* no-op */
#define LogLoggerDebug /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#ifdef DEBUG
#define LogInfo(fmt, ...)                LogAtLevel_debug(NULL,   Info, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#define LogLoggerInfo(logger, fmt, ...)  LogAtLevel_debug(logger, Info, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogInfo(fmt, ...)                LogAtLevel_nodebug(NULL,   Info, fmt, ## __VA_ARGS__)
#define LogLoggerInfo(logger, fmt, ...)  LogAtLevel_nodebug(logger, Info, fmt, ## __VA_ARGS__)
#endif
#else
#define LogInfo        /* no-op */
#define LogLoggerInfo  /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#ifdef DEBUG
#define LogWarn(fmt, ...)                LogAtLevel_debug(NULL,   Warn, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#define LogLoggerWarn(logger, fmt, ...)  LogAtLevel_debug(logger, Warn, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogWarn(fmt, ...)                LogAtLevel_nodebug(NULL,   Warn, fmt, ## __VA_ARGS__)
#define LogLoggerWarn(logger, fmt, ...)  LogAtLevel_nodebug(logger, Warn, fmt, ## __VA_ARGS__)
#endif
#else
#define LogWarn        /* no-op */
#define LogLoggerWarn  /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#ifdef DEBUG
#define LogError(fmt, ...)               LogAtLevel_debug(NULL,   Error, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#define LogLoggerError(logger, fmt, ...) LogAtLevel_debug(logger, Error, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogError(fmt, ...)               LogAtLevel_nodebug(NULL,   Error, fmt, ## __VA_ARGS__)
#define LogLoggerError(logger, fmt, ...) LogAtLevel_nodebug(logger, Error, fmt, ## __VA_ARGS__)
#endif
#else
#define LogError       /* no-op */
#define LogLoggerError /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_FATAL
#ifdef DEBUG
#define LogFatal(fmt, ...)               LogAtLevel_debug(NULL,   Fatal, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#define LogLoggerFatal(logger, fmt, ...) LogAtLevel_debug(logger, Fatal, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogFatal(fmt, ...)               LogAtLevel_nodebug(NULL,   Fatal, fmt, ## __VA_ARGS__)
#define LogLoggerFatal(logger, fmt, ...) LogAtLevel_nodebug(logger, Fatal, fmt, ## __VA_ARGS__)
#endif
#else
#define LogFatal       /* no-op */
#define LogLoggerFatal /* no-op */
#endif

#endif // defined __LIBLOG_LOG_H__
