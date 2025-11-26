module;
#include <CoreFoundation/CoreFoundation.h>

extern "C" void NSLog(CFStringRef format, ...);

module silog;

void silog::impl::log(log_level lvl, sv msg) {
  NSLog(CFSTR("[%s] %.*s"),
      impl::log_level_cstr(lvl),
      static_cast<unsigned>(msg.size()),
      msg.begin());
}
