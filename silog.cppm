export module silog;
export import :base;
import jute;

// TODO: allow removal of debug logs somehow
export namespace silog {
  __attribute__((format(printf, 2, 3))) void log(log_level lvl, const char * msg, ...);
  [[noreturn]] __attribute__((format(printf, 1, 2))) void die(const char * msg, ...);
  [[noreturn]] __attribute__((format(printf, 1, 2))) void whilst(const char * msg, ...);

  inline void assert(bool cond, log_level lvl, const char * msg) {
    if (!cond) log(lvl, "%s", msg);
  }
  inline void assert(bool cond, const char * msg) { assert(cond, error, msg); }

  inline void trace(jute::view msg, unsigned n) {
    log(debug, "%.*s: %d", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(jute::view msg, int n) {
    log(debug, "%.*s: %d", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(jute::view msg, long long n) {
    log(debug, "%.*s: %lld", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(jute::view msg, unsigned long long n) {
    log(debug, "%.*s: %lld", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(jute::view msg, float n) {
    log(debug, "%.*s: %f", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(jute::view msg, const void * n) {
    log(debug, "%.*s: %p", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(jute::view msg, const char * n) {
    log(debug, "%.*s: %s", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(jute::view msg, jute::view str) {
    log(debug, "%.*s: [%.*s]", static_cast<unsigned>(msg.size()), msg.data(), static_cast<unsigned>(str.size()),
        str.data());
  }
  inline void trace(jute::view msg, jute::heap str) { trace(msg, *str); }

  inline void trace(auto x) { trace(jute::view { "value" }, x); }
} // namespace silog

namespace silog::impl {
  constexpr inline auto log_level_cstr(silog::log_level lvl) {
    switch (lvl) {
      case silog::debug: return "debug";
      case silog::error: return "error";
      case silog::info: return "info";
      case silog::warning: return "warning";
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
#elif LECO_TARGET_WASM
#pragma leco add_impl wasm sprintf
#elif __linux__
#pragma leco add_impl linux sprintf
#endif
