module;
#include <CoreFoundation/CoreFoundation.h>

extern "C" void NSLog(CFStringRef format, ...);

module silog;

void silog::impl::log(log_level lvl, sv msg) {
  auto c = fprintf(stdout, "[%5s] %.*s\n",
      impl::log_level_cstr(lvl),
      static_cast<unsigned>(msg.size()),
      msg.begin());
  if (c > 0) return;

  NSLog(CFSTR("[%s] %.*s"),
      impl::log_level_cstr(lvl),
      static_cast<unsigned>(msg.size()),
      msg.begin());
}
