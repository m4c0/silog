#include "silog.hpp"

#include <android/log.h>

// TODO: fetch the app name somehow
void silog::log(silog::log_level lvl, const char * msg) {
  switch (lvl) {
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
