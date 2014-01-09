cut = Clean C Unit Testing

## Example

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
#include "cut.h"

void your_suite();
int main (int argc, char const *argv[]) {
  cut_run_suite(your_suite);
  cut_print_stats();
  return 0;
}
```

Add cut.h and cut.c and compile and run

```sh
$ cc std=c11 your_suite.c test_runner.c cut.c && ./a.out

your_suite
  foo1 .Success
  foo2 10: Expected 1, but got 2
  bar 14: Pending
  baz .19: Failure

4 tests, 1 success, 2 failure, 1 pending
2 assertions passed
```

## Sweet spots

`assert_eq` is robust for nul-terminated string comparison

```c
char a[] = "foo";
assert_eq("foo", a);
assert_neq((void*)"foo", (void*)a); // in case you want to compare pointers
```

`assert_arr_eq` is for array content comparison. To compare 2 arrays:

```c
assert_eq(arr1_size, arr2_size);
assert_arr_eq(arr1_size, arr1, arr2);
```

## Caveats

Require C11 for type generic macros.

Every suite is a function of state machine, tests are run in the definition order (random order is a todo).

Code outside the `test(...){ ... }` blocks will be executed n+1 times, where n is the number of tests (`before_each`/`after_each` are todos).

## Usage

- `test(test_name) { ... }` - define a test (must be put inside a void function)
- `cut_run_suite(your_suite)` - run a test suite
- `cut_print_stats()` - print test stats

## Assertions (todo)

- `assert_true(actual, message)` - if actual, then success, else show message
- `assert_eq(expected, actual)` - it will use string comparison when given char* data
- `assert_arr_eq(len, expected, actual)` - array compare with length
- `assert_eps_eq(eps, expected, actual)` - floating point compare with eps
- `assert_prec_eq(prec, expected, actual)` - precision based predicate

## Negative assertions (todo)

- `assert_false`
- `assert_neq`
- `assert_arr_neq`
- `assert_eps_neq`
- `assert_prec_neq`

## License

In-file BSD 3-clause.
