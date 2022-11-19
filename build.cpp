#include "ecow.hpp"

using namespace ecow;

int main(int argc, char ** argv) {
  seq all { "all" };

  auto m = all.add_unit<per_feat<mod>>("silog");
  m->add_feat<js>()->set("silog_log", R"((ptr) => {
  const view = new Uint8Array(ecow_buffer);
  var str = '';
  while (view[ptr] != 0) {
    str += String.fromCharCode(view[ptr]);
    ptr++;
  }
  console.log(str);
})");

  auto & m_steve = m->for_feature(objective_c);
  m_steve.add_impl("silog.apple");
  m_steve.add_unit<objc>("apple");

  auto & m_oreo = m->for_feature(android_ndk);
  m_oreo.add_impl("silog.android");
  // This may be a bug, but we don't need this using ecow (somehow)
  // m_oreo.add_system_library("log");

  m->for_feature(webassembly).add_impl("silog.wasm");
  m->for_feature(windows_api).add_impl("silog.windows");

  // Tests if we link properly. Can be run on Mac and Windows
  auto poc = all.add_unit<app>("silog-poc");
  poc->add_feat<js>()->set("main", "");
  poc->add_ref(m);
  poc->add_unit<>("poc");

  return run_main(all, argc, argv);
}
