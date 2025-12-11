module silog;
import print;
import vaselin;

void silog::impl::log(silog::log_level lvl, sv msg) {
  auto level = silog::impl::log_level_cstr(lvl);
  if (lvl == silog::error) {
    errln("[", level, "] ", msg);
  } else {
    putln("[", level, "] ", msg);
  }
}
