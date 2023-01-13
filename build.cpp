#include "build.hpp"

using namespace ecow;

int main(int argc, char ** argv) {
  seq all { "all" };

  // Tests if we link properly. Can be run on Mac and Windows
  auto poc = all.add_unit<app>("silog-poc");
  poc->add_feat<js>()->set("main", "");
  poc->add_ref(silog());
  poc->add_unit<>("poc");

  return run_main(all, argc, argv);
}
