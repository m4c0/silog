#pragma once
#include "ecow.hpp"

auto silog() {
  using namespace ecow;

  auto m = unit::create<per_feat<mod>>("silog");
  m->add_feat<inline_js>("silog_log", R"((ptr) => {
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
  auto & m_wasm = m->for_feature(webassembly);
  auto & m_bill = m->for_feature(windows_api);

  return m;
}
