module;
#include <filesystem>
#include <windows.h>

module silog;

static HANDLE g_mutex = nullptr;

class mutex {
public:
  mutex() {
    // FIXME: not really atomic
    if (g_mutex == nullptr) g_mutex = CreateMutex(nullptr, false, nullptr);
    if (g_mutex != nullptr) WaitForSingleObject(g_mutex, INFINITE);
  }
  ~mutex() {
    if (g_mutex != nullptr && !ReleaseMutex(g_mutex)) g_mutex = nullptr;
  }
};
class file {
  HANDLE m_h;

public:
  file(const char * name) {
    m_h = CreateFile(name, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    SetFilePointer(m_h, 0, nullptr, FILE_END);
  }
  ~file() {
    CloseHandle(m_h);
  }

  void write(const char * data) {
    DWORD out;
    WriteFile(m_h, data, strlen(data), &out, nullptr);
  }
};

static char logpath[MAX_PATH + 1] {};
void silog::impl::log(silog::log_level lvl, const char * msg) {
  mutex m {};

  SYSTEMTIME lt;
  GetLocalTime(&lt);

  auto level = silog::impl::log_level_cstr(lvl);

  if (logpath[0] == 0) {
    if (GetModuleFileName(0, logpath, sizeof(logpath) - 1) == 0) return;

    auto ext = strrchr(logpath, '.');
    if (ext == nullptr) return;

    int rem = ext - logpath;
    if (rem > sizeof(logpath) - 4) return;
    strncpy_s(ext + 1, rem, "log", 3);
  }

  char buf[1024] {};
  snprintf(
      buf,
      sizeof(buf) - 1,
      "%04d-%02d-%02d %02d:%02d:%02d.%03d [%s] %s\n",
      lt.wYear,
      lt.wMonth,
      lt.wDay,
      lt.wHour,
      lt.wMinute,
      lt.wSecond,
      lt.wMilliseconds,
      level,
      msg);

  file f { logpath };
  f.write(buf);
}
