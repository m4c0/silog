export module silog;
export import :base;

export namespace silog {
  __attribute__((format(printf, 2, 3))) void log(log_level lvl, const char * msg, ...);

  inline void assert(bool cond, log_level lvl, const char * msg) {
    // TODO: allow removal of this using some flag
    if (!cond) log(lvl, "%s", msg);
  }
}

namespace silog::impl {
  static auto log_level_cstr(silog::log_level lvl) {
    switch (lvl) {
    case silog::debug:
      return "debug";
    case silog::error:
      return "error";
    case silog::info:
      return "info";
    case silog::warning:
      return "warning";
    }
  }
}

#if __ANDROID__
#pragma ecow add_impl android sprintf
#pragma ecow add_system_library log
#elif __APPLE__
#pragma ecow add_impl apple sprintf
#pragma ecow add_framework Foundation
#elif WIN32
#pragma ecow add_impl sprintf windows
#elif WASM
#pragma ecow add_impl wasm
#endif
