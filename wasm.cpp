module;
#include <stdio.h>

extern "C" void __attribute__((import_name("silog_log"))) silog_log(const char * msg);

module silog;

void silog::impl::log(silog::log_level lvl, const char * msg) {
  auto level = silog::impl::log_level_cstr(lvl);

  char buf[10240];
  sprintf(buf, "[%s] %s", level, msg);
  silog_log(buf);
}
