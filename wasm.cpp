module;
#include <stdio.h>

module silog;

void silog::impl::log(silog::log_level lvl, const char * msg) {
  auto level = silog::impl::log_level_cstr(lvl);
  printf("[%s] %s\n", level, msg);
}
