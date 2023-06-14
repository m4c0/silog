export module silog;
export import :base;

export namespace silog {
  __attribute__((format(printf, 2, 3))) void log(log_level lvl, const char * msg, ...);
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
