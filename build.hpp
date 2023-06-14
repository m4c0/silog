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
  m_steve.add_part("base");
  m_steve.add_impl("silog.apple");
  m_steve.add_unit<objc>("apple");
  m_steve.add_impl("sprintf");

  auto & m_oreo = m->for_feature(android_ndk);
  m_oreo.add_part("base");
  m_oreo.add_impl("silog.android");
  m_oreo.add_system_library("log");
  m_oreo.add_impl("sprintf");

  auto & m_wasm = m->for_feature(webassembly);
  m_wasm.add_part("base");
  m_wasm.add_impl("silog.wasm");
  m_wasm.add_impl("sprintf");

  auto & m_bill = m->for_feature(windows_api);
  m_bill.add_part("base");
  m_bill.add_impl("silog.windows");
  m_bill.add_impl("sprintf");

  return m;
}
