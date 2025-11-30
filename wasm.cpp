module;
#include <stdio.h>

module silog;
import vaselin;

void silog::impl::log(silog::log_level lvl, sv msg) {
  auto level = silog::impl::log_level_cstr(lvl);
  if (lvl == silog::error) {
    fprintf(stderr, "[%s] %s\n", level, msg);
  } else {
    printf("[%s] %s\n", level, msg);
  }
}
