import silog;

int __attribute__((export_name("main"))) main() {
  silog::log(silog::info, "I'm %s", "ok");
}
