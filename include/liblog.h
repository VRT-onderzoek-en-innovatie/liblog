#ifndef __LIBLOG_LOG_H__
#define __LIBLOG_LOG_H__

#include "liblog_level.h"
#include <stdio.h>

/* If the log-level is not specified,
   compile in all */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_TRACE
#endif

#ifdef __cplusplus
extern "C"{
#endif

enum LogDestination {
	uninitialized=0,
	Null,
	FileStream
	};

struct Log_logger {
	enum LogLevel current_log_level;
	enum LogDestination current_log_destination;
	FILE *log_destination_file_stream;
};


/* Initialize a new logger
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
int LogAtLevel(struct Log_logger *l,
               enum LogLevel level,
               const char *file, const char *func, const int lineNum,
               const char *fmt, ...);

#ifdef __cplusplus
}
#endif


#if LOG_LEVEL <= LOG_LEVEL_TRACE
#define LogTrace(fmt, ...) LogAtLevel(NULL, Trace, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogTrace /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LogDebug(fmt, ...) LogAtLevel(NULL, Debug, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogDebug /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LogInfo(fmt, ...)  LogAtLevel(NULL, Info, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogInfo  /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LogWarn(fmt, ...)  LogAtLevel(NULL, Warn, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogWarn  /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LogError(fmt, ...) LogAtLevel(NULL, Error, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogError /* no-op */
#endif

#if LOG_LEVEL <= LOG_LEVEL_FATAL
#define LogFatal(fmt, ...) LogAtLevel(NULL, Fatal, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)
#else
#define LogFatal /* no-op */
#endif

#endif // defined __LIBLOG_LOG_H__
