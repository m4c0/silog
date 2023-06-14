export module silog:base;

export namespace silog {
  enum log_level { debug, error, info, warning };
  __attribute__((format(printf, 2, 3))) void log(log_level lvl, const char * msg, ...);
}
namespace silog::impl {
  void log(log_level lvl, const char * msg);
}
