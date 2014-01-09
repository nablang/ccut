cut = Clean C Unit Testing

## example

your_suite.c

```c
#include "cut.h"

void your_suite() {

  test(foo1) {
    assert_true(2 == 2, "waze");
  }

  test(foo2) {
    assert_true(1 == 2, "no way");
  }

  test(bar) {
    pending;
  }

  test(baz) {
    assert_eq(1, 1);
    fail;
  }

}
```

test_runner.c

```c
void your_suite();
int main (int argc, char const *argv[]) {
  cut_run_suite(your_suite);
  cut_print_stats();
  return 0;
}
```

add cut.h and cut.c and compile and run

```sh
cc std=c11 your_suite.c test_runner.c cut.c && ./a.out
```

## sweet spots

`assert_eq` is robust for nul-terminated string comparison

```c
char a[] = "foo";
assert_eq("foo", a);
assert_neq((void*)"foo", (void*)a); // in case you want to compare pointers
```

`assert_arr_eq` is for array content comparison. to compare 2 arrays:

```c
assert_eq(arr1_size, arr2_size);
assert_arr_eq(arr1_size, arr1, arr2);
```

## caveats

require C11 for type generic macros.

every suite is a function of state machine, tests are run in the definition order (random order is a todo).

code outside the `test(...){ ... }` blocks will be executed n+1 times, where n is the number of tests (`before_each`/`after_each` are todos).

## usage

- `test(test_name) { ... }` define a test (must be put inside a void function)
- `cut_run_suite(your_suite)` run a test suite
- `cut_print_stats()` print test stats

## assertions and actions (todo)

- `assert_true(actual, message)` - if actual, then success, else show message
- `assert_eq(expected, actual)` - it will use string comparison when given char* data
- `assert_arr_eq(len, expected, actual)` - array compare with length
- `assert_eps_eq(eps, expected, actual)` - floating point compare with eps
- `assert_prec_eq(prec, expected, actual)` - precision based predicate

## negative assertions (todo)

- `assert_false`
- `assert_neq`
- `assert_arr_neq`
- `assert_eps_neq`
- `assert_prec_neq`
