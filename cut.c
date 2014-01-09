/**
Copyright (c) 2013, http://github.com/luikore/cut
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

* Neither the name of the {organization} nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#include "cut.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
  int runned_tests_cap;
  int runned_tests_size;
  const char** runned_tests;

  const char* current_name; // name of current test
  int current_state;  // 0: success, 1: pending, 2: failure

  int success_size;
  int failure_size;
  int pending_size;
  int assertion_size;
} CUTContext;

static CUTContext ctx = {
  0, 0, NULL,
  NULL, 0,
  0, 0, 0, 0
};

void __cut_run_suite(void (*s)()) {
  ctx.runned_tests_size = 0;
  ctx.runned_tests_cap = 8;
  ctx.runned_tests = malloc(sizeof(char*) * ctx.runned_tests_cap);

  ctx.current_name = NULL;
  ctx.current_state = 0;
  while (1) {
    int last_tests_size = ctx.runned_tests_size;
    s();
    if (last_tests_size == ctx.runned_tests_size) {
      // last success
      if (ctx.runned_tests_size && !ctx.current_state) {
        printf("\e[38;5;2mSuccess\e[38;5;7m");
        ctx.success_size++;
      }
      break;
    }
  }

  free(ctx.runned_tests);
  ctx.runned_tests_size = 0;
  ctx.runned_tests_cap = 0;
  ctx.runned_tests = NULL;
}

void __cut_print_stats() {
  int all = ctx.success_size + ctx.failure_size + ctx.pending_size;
  printf("\n\n%d tests, %d success, %d failure, %d pending\n%d assertions passed\n",
    all, ctx.success_size, ctx.failure_size, ctx.pending_size, ctx.assertion_size
  );
}

static void add_runned_test(const char* c) {
  ctx.current_name = c;
  printf("\n  %s ", c);
  if (ctx.runned_tests_size >= ctx.runned_tests_cap) {
    ctx.runned_tests_cap *= 2;
    ctx.runned_tests = realloc(ctx.runned_tests, sizeof(char*) * ctx.runned_tests_cap);
  }
  ctx.runned_tests[ctx.runned_tests_size++] = c;
}

static int test_runned(const char* c) {
  for (int i = 0; i < ctx.runned_tests_size; i++) {
    if (strcmp(ctx.runned_tests[i], c) == 0) {
      return 1;
    }
  }
  return 0;
}

int __cut_dispatch(const char* c) {
  if (!ctx.runned_tests) {
    fprintf(stderr, "Please use cut_run_suite(suite_func) to run the tests");
    _Exit(1);
  }

  if (test_runned(c)) {
    return 0;
  }

  // no current_name, we are clean to start first run of the test
  if (!ctx.current_name) {
    add_runned_test(c);
    return 1;
  }

  // c != current_name, last test finished, start new test
  if (strcmp(ctx.current_name, c)) {
    if (!ctx.current_state) {
      printf("\e[38;5;2mSuccess\e[38;5;7m");
      ctx.success_size++;
    }
    add_runned_test(c);
    return 1;
  }

  // c == current_name, last test should have been failed
  if (ctx.current_state != 1 && ctx.current_state != 2) {
    fprintf(stderr, "return called from %s", ctx.current_name);
  }
  return 0;
}

void __cut_pending(int line) {
  printf("\e[38;5;3m%d: Pending\e[38;5;7m", line);
  ctx.pending_size++;
  ctx.current_state = 1;
}

void __cut_fail_before(int line) {
  printf("\e[38;5;1m%d: ", line);
  ctx.failure_size++;
  ctx.current_state = 2;
}

void __cut_fail_after() {
  printf("\e[38;5;7m ");
}

void __cut_inc_assertion_size() {
  printf("\e[38;5;2m.\e[38;5;7m");
  ctx.assertion_size++;
}
