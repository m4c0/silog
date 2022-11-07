#include "ecow.hpp"

using namespace ecow;

int main(int argc, char ** argv) {
  seq all { "all" };

  auto m = all.add_unit<per_feat<mod>>("silog");

  auto & m_steve = m->for_feature(unit::feats::objective_c);
  m_steve.add_impl("silog.apple");
  m_steve.add_unit<objc>("apple.mm")->add_framework("Foundation");

  auto & m_oreo = m->for_feature(unit::feats::android_ndk);
  m_oreo.add_impl("silog.android");
  // This may be a bug, but we don't need this using ecow (somehow)
  // m_oreo.add_system_library("log");

  m->for_feature(unit::feats::windows_api).add_impl("silog.windows");

  // Tests if we link properly. Can be run on Mac and Windows
  auto poc = all.add_unit<exe>("silog-poc");
  poc->add_ref(m);
  poc->add_unit<>("poc");

  return run_main(all, argc, argv);
}
