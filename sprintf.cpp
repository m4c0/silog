module;
#include <stdarg.h>
#include <stdio.h>

module silog;
import :base;

namespace {
  /// Exception class. Not meant to be caught. Use your own types if you want
  /// to catch exceptions.
  struct death {};
} // namespace

void silog::log(log_level lvl, const char * msg, ...) {
  char buf[1024];

  va_list arg;
  va_start(arg, msg);
  vsnprintf(buf, 1024, msg, arg);
  va_end(arg);

  impl::log(lvl, buf);
}
void silog::die(const char * msg, ...) {
  char buf[1024];

  va_list arg;
  va_start(arg, msg);
  vsnprintf(buf, 1024, msg, arg);
  va_end(arg);

  impl::log(error, buf);
  throw death {};
}
void silog::whilst(const char * msg, ...) {
  char buf[1024] = "while ";

  va_list arg;
  va_start(arg, msg);
  vsnprintf(buf + 6, 1024 - 6, msg, arg);
  va_end(arg);

  impl::log(error, buf);
  throw;
}
