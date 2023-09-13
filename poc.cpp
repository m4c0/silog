#pragma leco tool

import silog;

#if __wasm__
#define WASM_MAIN __attribute__((export_name("main")))
#else
#define WASM_MAIN
#endif

int WASM_MAIN main() {
  silog::log(silog::info, "I'm %s", "ok");
  silog::assert(true, silog::debug, "I'm kinda ok");
  silog::assert(false, "I'm not ok");
}
