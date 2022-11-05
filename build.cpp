#include "ecow.hpp"

using namespace ecow;

int main(int argc, char ** argv) {
  seq all { "all" };

  auto m = all.add_unit<mod>("silog");

#ifdef __APPLE__
  m->add_impl("silog.apple");
  m->add_unit("apple.mm");
  m->add_framework("Foundation");
#elif _WIN32
  m->add_impl("silog.windows");
#endif

  auto poc = all.add_unit<app>("silog-poc");
  poc->add_ref(m);
  poc->add_unit<>("poc");

  return run_main(all, argc, argv);
}
