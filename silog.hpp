#pragma once

namespace silog {
  enum log_level { error, info, warning };
  void log(log_level lvl, const char * msg);
}
