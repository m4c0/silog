#pragma leco app

import silog;

int main() {
  silog::log(silog::info, "I'm %s", "ok");
  silog::assert(true, "I'm kinda ok");
  try {
    silog::die("I'm defo %s ok", "not");
    silog::log(silog::error, "reach the unreachable");
  } catch (...) {
    silog::log(silog::debug, "got expected exception");
  }

  // New API version
  silog::info("This is info on V2");
  silog::infof("This is %s info", "also");

  try {
    silog::assert(false, "I'm not ok");
    silog::error("failed assertion did not raise error");
  } catch (...) {
  }
}
