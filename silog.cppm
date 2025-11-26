export module silog;
import sv;

export namespace silog {
  using log_level = void (*)(sv);
  __attribute__((format(printf, 2, 3))) void log(log_level lvl, const char * msg, ...);
}
namespace silog::impl {
  void log(log_level lvl, sv msg);
}

export namespace silog {
  __attribute__((format(printf, 2, 3))) void log(log_level lvl, const char * msg, ...);
  [[noreturn]] __attribute__((format(printf, 1, 2))) void die(const char * msg, ...);
  [[noreturn]] __attribute__((format(printf, 1, 2))) void whilst(const char * msg, ...);

  void debug(sv msg) { impl::log(debug, msg); }
  void error(sv msg) { impl::log(error, msg); }
  void info(sv msg) { impl::log(info, msg); }
  void warning(sv msg) { impl::log(warning, msg); }

  void debugf(const char * msg, auto ... p) { log(debug, msg, p...); }
  void errorf(const char * msg, auto ... p) { log(error, msg, p...); }
  void infof(const char * msg, auto ... p) { log(info, msg, p...); }
  void warningf(const char * msg, auto ... p) { log(warning, msg, p...); }

  inline void assert(bool cond, const char * msg) {
    if (cond) return;
    die("%s", msg);
  }

  inline void trace(sv msg, unsigned n) {
    log(debug, "%.*s: %d", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(sv msg, int n) {
    log(debug, "%.*s: %d", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(sv msg, long long n) {
    log(debug, "%.*s: %lld", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(sv msg, unsigned long long n) {
    log(debug, "%.*s: %lld", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(sv msg, float n) {
    log(debug, "%.*s: %f", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(sv msg, const void * n) {
    log(debug, "%.*s: %p", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(sv msg, const char * n) {
    log(debug, "%.*s: %s", static_cast<unsigned>(msg.size()), msg.data(), n);
  }
  inline void trace(sv msg, sv str) {
    log(debug, "%.*s: [%.*s]", static_cast<unsigned>(msg.size()), msg.data(), static_cast<unsigned>(str.size()),
        str.data());
  }

  inline void trace(auto x) { trace("value"_sv, x); }
} // namespace silog

namespace silog::impl {
  constexpr inline auto log_level_cstr(silog::log_level lvl) {
    if (lvl == silog::debug)   return "debug";
    if (lvl == silog::error)   return "error";
    if (lvl == silog::info)    return "info";
    if (lvl == silog::warning) return "warning";
    return "debug";
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
