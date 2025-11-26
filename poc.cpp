#pragma leco app

import silog;

int main() {
  silog::log(silog::info, "I'm %s", "ok");
  silog::assert(true, "I'm kinda ok");
  silog::assert(false, "I'm not ok");
  try {
    silog::die("I'm defo %s ok", "not");
    silog::log(silog::error, "reach the unreachable");
  } catch (...) {
    silog::log(silog::debug, "got expected exception");
  }
}
