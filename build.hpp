#pragma once
#include "../ecow/ecow.hpp"

auto silog() {
  using namespace ecow;

  auto m = unit::create<mod>("silog");
  m->add_feat<inline_js>("silog_log", R"((ptr) => {
  const view = new Uint8Array(ecow_buffer);
  var str = '';
  while (view[ptr] != 0) {
    str += String.fromCharCode(view[ptr]);
    ptr++;
  }
  console.log(str);
})");
  return m;
}
