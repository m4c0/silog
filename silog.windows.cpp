module;
#include <exception>
#include <filesystem>
#include <fstream>
#include <tchar.h>
#include <windows.h>

module silog;

static auto exe_path() noexcept {
  TCHAR exepath[MAX_PATH + 1];

  if (GetModuleFileName(0, exepath, MAX_PATH + 1) == 0) {
    std::terminate();
  }

  return std::filesystem::path { exepath };
}
void silog::impl::log(silog::log_level lvl, const char * msg) {
  std::time_t t = std::time(nullptr);
  std::tm * tm = std::localtime(&t);

  auto exe = exe_path();
  auto level = silog::impl::log_level_cstr(lvl);
  std::ofstream out { exe.replace_extension(".log"), std::ios::app };
  out << std::put_time(tm, "%F %T %z") << " [" << level << "] " << msg << std::endl;
}
