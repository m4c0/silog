module;
extern "C" void silog_nslog(const char * lvl, const char * msg);

module silog;

void silog::impl::log(log_level lvl, const char * msg) {
  silog_nslog(impl::log_level_cstr(lvl), msg);
}
