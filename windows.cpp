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

  auto size() {
    LARGE_INTEGER sz{};
    return GetFileSizeEx(m_h, &sz) ? sz.QuadPart : 0;
  }

  void write(const char * data) {
    DWORD out;
    WriteFile(m_h, data, strlen(data), &out, nullptr);
  }
};

static bool write(const char * logpath, const char * msg) {
  file f { logpath };
  if (f.size() > 10 * 1024 * 1024)
    return false;

  f.write(msg);
  return true;
}

static char logpath[MAX_PATH + 1] {};
static char bkppath[MAX_PATH + 1] {};
void silog::impl::log(silog::log_level lvl, sv msg) {
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

    strncpy_s(bkppath, sizeof(bkppath), logpath, sizeof(logpath));
    bkppath[strlen(bkppath) - 1] = '_';
  }

  char buf[1024] {};
  snprintf(
      buf,
      sizeof(buf) - 1,
      "%04d-%02d-%02d %02d:%02d:%02d.%03d [%s] %.*s\n",
      lt.wYear,
      lt.wMonth,
      lt.wDay,
      lt.wHour,
      lt.wMinute,
      lt.wSecond,
      lt.wMilliseconds,
      level,
      static_cast<unsigned>(msg.size()),
      msg.begin());

  // Print to stdout when available. This is useful for `main` apps but it
  // won't appear on `WinMain` apps.
  fprintf(stdout, "%s", buf);
  if (!write(logpath, buf)) {
    MoveFileEx(logpath, bkppath, MOVEFILE_REPLACE_EXISTING);
    write(logpath, buf);
  }
}
