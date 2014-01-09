#include <stdio.h>


//// main specific


void __cut_run_suite(void (*)());
void __cut_print_stats();

#define cut_run_suite(__suite)\
  printf("\n\e[38;5;6m" #__suite "\e[38;5;7m");\
  __cut_run_suite(__suite);

#define cut_print_stats\
  __cut_print_stats


//// suite specific


int __cut_dispatch(const char* c);
void __cut_fail_before(int line);
void __cut_fail_after();
void __cut_pending(int line);
void __cut_inc_assertion_size();

#define test(c)\
  if (__cut_dispatch(#c))

#define pending\
  __cut_pending(__LINE__);\
  return

#define fail\
  __cut_fail_before(__LINE__);\
  printf("Failure");\
  __cut_fail_after();\
  return

#define assert_true(expr, ...)\
  if (expr) {\
    __cut_inc_assertion_size();\
  } else {\
    __cut_fail_before(__LINE__);\
    printf(__VA_ARGS__);\
    __cut_fail_after();\
    return;\
  }

// todo many other types
#define assert_eq(expected, actual)\
  assert_true(expected == actual, "Expected %lld, but got %lld", expected, actual)
