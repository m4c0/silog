#import <Foundation/Foundation.h>

extern "C" void silog_nslog(const char * lvl, const char * msg) {
  NSLog(@"[%s] %s", lvl, msg);
}
