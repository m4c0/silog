module;
#include <stdio.h>

module silog;
import vaselin;

void silog::impl::log(silog::log_level lvl, const char * msg) {
  auto level = silog::impl::log_level_cstr(lvl);
  switch (lvl) {
  case silog::error:
    fprintf(stderr, "[%s] %s\n", level, msg);
    break;
  default:
    printf("[%s] %s\n", level, msg);
    break;
  }
}
