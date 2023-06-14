module;
#include <stdarg.h>
#include <stdio.h>

module silog:sprintf;
import :base;

void silog::log(log_level lvl, const char * msg, ...) {
  char buf[1024];

  va_list arg;
  va_start(arg, msg);
  vsnprintf(buf, 1024, msg, arg);
  va_end(arg);

  impl::log(lvl, buf);
}
