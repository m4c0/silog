export module silog;

export namespace silog {
  enum log_level { debug, error, info, warning };
  void log(log_level lvl, const char * msg);
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
