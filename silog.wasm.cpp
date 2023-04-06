module;
#include <sstream>

extern "C" void __attribute__((import_name("silog_log"))) silog_log(const char * msg);

module silog;

void silog::log(silog::log_level lvl, const char * msg) {
  auto level = silog::impl::log_level_cstr(lvl);
  std::stringstream buf {};
  buf << "[" << level << "] " << msg;

  const auto str = buf.str();
  silog_log(str.c_str());
}
