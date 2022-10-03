#include "common.hpp"
#include "silog.hpp"

#include <sstream>

extern "C" void silog_log(const char * msg);

void silog::log(silog::log_level lvl, const char * msg) {
  auto level = silog::impl::log_level_cstr(lvl);
  std::stringstream buf {};
  buf << "[" << level << "] " << msg;

  const auto str = buf.str();
  silog_log(str.c_str());
}
