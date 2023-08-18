module;
#include <CoreFoundation/CoreFoundation.h>

extern "C" void NSLog(CFStringRef format, ...);

module silog;

void silog::impl::log(log_level lvl, const char * msg) {
  NSLog(CFSTR("[%s] %s"), impl::log_level_cstr(lvl), msg);
}
