import silog;

int __attribute__((export_name("main"))) main() {
  silog::log(silog::info, "I'm %s", "ok");
  silog::assert(true, silog::debug, "I'm kinda ok");
  silog::assert(false, "I'm not ok");
}
