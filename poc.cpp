import silog;

int main() {
  silog::log(silog::info, "ok");
}

// Just for wasm, it doesn't matter for other platforms
extern "C" void silog_log(const char *) {
}
