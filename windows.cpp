module;
#include <exception>
#include <filesystem>
#include <fstream>
#include <tchar.h>
#include <windows.h>

module silog;

static HANDLE g_mutex = nullptr;

static auto exe_path() noexcept {
  TCHAR exepath[MAX_PATH + 1];

  if (GetModuleFileName(0, exepath, MAX_PATH + 1) == 0) {
    std::terminate();
  }

  return std::filesystem::path { exepath };
}

class mutex {
public:
  mutex() {
    if (g_mutex == nullptr) g_mutex = CreateMutex(nullptr, false, nullptr);
    if (g_mutex != nullptr) WaitForSingleObject(g_mutex, INFINITE);
  }
  ~mutex() {
    if (g_mutex != nullptr && !ReleaseMutex(g_mutex)) g_mutex = nullptr;
  }
};

void silog::impl::log(silog::log_level lvl, const char * msg) {
  mutex m {};

  std::tm tm;
  std::time_t t = std::time(nullptr);
  localtime_s(&tm, &t);

  auto exe = exe_path();
  auto level = silog::impl::log_level_cstr(lvl);
  std::ofstream out { exe.replace_extension(".log"), std::ios::app };
  out << std::put_time(&tm, "%F %T %z") << " [" << level << "] " << msg << std::endl;
}
