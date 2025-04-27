#ifndef LOGGING_H
#define LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

enum log_level_e {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL
};

struct text_color_t {
  int foreground, background;
};

static const char *__log_level_strings[] = {"DEBUG", "INFO", "WARN", "ERROR",
                                            "FATAL"};

static const struct text_color_t __log_level_colors[] = {
    {35, 49},  // LOG_LEVEL_DEBUG
    {34, 49},  // LOG_LEVEL_INFO
    {33, 49},  // LOG_LEVEL_WARN
    {31, 49},  // LOG_LEVEL_ERROR
    {30, 101}, // LOG_LEVEL_FATAL
};

#define log_debug(...)                                                         \
  logger_log(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)                                                          \
  logger_log(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)                                                          \
  logger_log(LOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)                                                         \
  logger_log(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...)                                                         \
  logger_log(LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void logger_log(enum log_level_e level, const char *file, int line,
                const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif // !#ifndef LOGGING_H
