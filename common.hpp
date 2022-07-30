#pragma once

#include "silog.hpp"

namespace silog::impl {
  static auto log_level_cstr(silog::log_level lvl) {
    switch (lvl) {
    case silog::error:
      return "error";
    case silog::info:
      return "info";
    case silog::warning:
      return "warning";
    }
  }
}
