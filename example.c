#include "cut.h"

void your_suite() {

  test(foo1) {
    assert_true(2 == 2, "waze");
  }

  test(foo2) {
    assert_eq(1, 2);
  }

  test(bar) {
    pending;
  }

  test(baz) {
    assert_eq(1, 1);
    fail;
  }

}

int main (int argc, char const *argv[]) {
  cut_run_suite(your_suite);
  cut_print_stats();
  return 0;
}
