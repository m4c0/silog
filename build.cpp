#include "ecow.hpp"

using namespace ecow;

int main() {
  seq all { "all" };

  auto lib = all.add_unit<seq>("all objects");

  auto m = lib->add_unit<mod>("silog");

#ifdef __APPLE__
  m->add_impl("silog.apple");
  lib->add_unit("apple");
#elif _WIN32
  m->add_impl("silog.windows");
#endif

  auto poc = all.add_unit<exe>("silog-poc");
  poc->add_ref(lib);
  poc->add_unit<>("poc");

  return all.build() ? 0 : 1;
}
