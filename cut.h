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

#pragma once

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
  assert_true(expected == actual, "Expected %lld, but got %lld", (long long)expected, (long long)actual)
