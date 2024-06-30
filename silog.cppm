export module silog;
export import :base;
import jute;

// TODO: allow removal of debug logs somehow
export namespace silog {
  __attribute__((format(printf, 2, 3))) void log(log_level lvl, const char * msg, ...);

  inline void assert(bool cond, log_level lvl, const char * msg) {
    if (!cond) log(lvl, "%s", msg);
  }
  inline void assert(bool cond, const char * msg) {
    assert(cond, error, msg);
  }

  inline void log_failure(jute::view msg) {
    log(error, "Unexpected failure: %.*s", static_cast<unsigned>(msg.size()), msg.data());
  }

  struct unexpected_failure {};
  inline void fail(jute::view msg) {
    log_failure(msg);
    throw unexpected_failure();
  }
} // namespace silog

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
} // namespace silog::impl

#if __ANDROID__
#pragma leco add_impl android sprintf
#pragma leco add_library log
#elif __APPLE__
#pragma leco add_impl apple sprintf
#pragma leco add_framework Foundation
#elif _WIN32
#pragma leco add_impl sprintf windows
#elif WASM
#pragma leco add_impl wasm
#elif __linux__
#pragma leco add_impl linux sprintf
#endif
