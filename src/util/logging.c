#include "util/logging.h"

#include <stdio.h>
#include <time.h>

void logger_log(enum log_level_e level, const char *file, int line,
                const char *fmt, ...) {
#ifndef LOGGING_STOP
  va_list args;
  va_start(args, fmt);

  char buf[16];

  time_t t = time(NULL);
  strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&t));

#ifdef LOGGING_COLOR
  struct text_color_t col = __log_level_colors[level];
  printf("\x01\x1b[0m\x02\x01\x1b[90m\x02%s\x01\x1b[0m\x02  "
         "\x01\x1b[%d;%dm\x02%s\x01\x1b[0m\x02  "
         "\x01\x1b[90m\x02%s:%d\x01\x1b[0m\x02 "
         "\x01\x1b[37m\x02",
         buf, col.foreground, col.background, __log_level_strings[level], file,
         line);
#else
  printf("%s %s %s:%d -> ", buf, __log_level_strings[level], file, line);
#endif // LOGGING_COLOR

  vprintf(fmt, args);
  printf("\n");

  va_end(args);
#endif // LOGGING_STOP
}
