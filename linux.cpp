module;
#include <stdio.h>
#include <time.h>

module silog;

void silog::impl::log(silog::log_level lvl, const char * msg) {
  auto t = time(nullptr);
  auto tm = localtime(&t);

  char buf[26]{};
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);

  auto level = silog::impl::log_level_cstr(lvl);

  printf("%s [%s] %s\n", buf, level, msg);
}

