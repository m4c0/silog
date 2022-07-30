#include "common.hpp"
#include "silog.hpp"

#include <exception>
#include <filesystem>
#include <fstream>
#include <tchar.h>
#include <windows.h>

static auto exe_path() noexcept {
  TCHAR exepath[MAX_PATH + 1];

  if (GetModuleFileName(0, exepath, MAX_PATH + 1) == 0) {
    std::terminate();
  }

  return std::filesystem::path { exepath };
}
void silog::log(silog::log_level lvl, const char * msg) {
  std::time_t t = std::time(nullptr);
  std::tm tm {};
  localtime_s(&tm, &t);

  auto exe = exe_path();
  auto level = silog::impl::log_level_cstr(lvl);
  std::ofstream out { exe.replace_extension(".log"), std::ios::app };
  out << std::put_time(&tm, "%F %T %z") << " [" << level << "] " << msg << std::endl;
}
