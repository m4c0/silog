module;
#include <android/log.h>

module silog;

// TODO: fetch the app name somehow
void silog::impl::log(silog::log_level lvl, const char * msg) {
  switch (lvl) {
  case silog::debug:
    __android_log_print(ANDROID_LOG_DEBUG, "silog", "%s", msg);
    break;
  case silog::error:
    __android_log_print(ANDROID_LOG_ERROR, "silog", "%s", msg);
    break;
  case silog::info:
    __android_log_print(ANDROID_LOG_INFO, "silog", "%s", msg);
    break;
  case silog::warning:
    __android_log_print(ANDROID_LOG_WARN, "silog", "%s", msg);
    break;
  }
}
