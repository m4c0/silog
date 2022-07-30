#include "silog.hpp"
#include "common.hpp"

#import <Foundation/Foundation.h>

void silog::log(silog::log_level lvl, const char * msg) {
  NSLog(@"[%s] %s", silog::impl::log_level_cstr(lvl), msg);
}
