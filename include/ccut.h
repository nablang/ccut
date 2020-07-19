/**
Copyright (c) 2013-2020, http://github.com/luikore/ccut
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
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

  void __ccut_run_suite(const char* sname, void (*s)());
  void __ccut_print_stats();
  int __ccut_dispatch(const char* c);
  int __ccut_pending(int line);
  int __ccut_fail(int line);
  int __ccut_assert_true(int line, int expr, const char* msg, ...);
  int __ccut_assert_ll_eq(int line, long long expected, long long actual);
  int __ccut_assert_ll_neq(int line, long long expected, long long actual);
  int __ccut_assert_truef(int line, int predicate, void* expected, void* actual, void inspectf(void*));
  int __ccut_assert_falsef(int line, int predicate, void* expected, void* actual, void inspectf(void*));

#ifdef __cplusplus
}
#endif

//// main specific

#include <signal.h>
void ccut_print_trace_on(int sig);

#define ccut_run_suite(__suite)\
  __ccut_run_suite(#__suite, __suite)

#define ccut_print_stats()\
  __ccut_print_stats()

//// suite specific

#ifdef ccut_test
#undef ccut_test
#endif

#define ccut_test(c)\
  if (__ccut_dispatch(#c))

#ifdef pending
#undef pending
#endif

#define pending\
  if (__ccut_pending(__LINE__)) return

#ifdef fail
#undef fail
#endif

#define fail\
  if (__ccut_fail(__LINE__)) return

// NOTE since we don't care the type of expr, we use !! to turn it into int
#define assert_true(expr, ...)\
  if (__ccut_assert_true(__LINE__, !!(expr), __VA_ARGS__)) return

#define assert_false(expr, ...)\
  if (__ccut_assert_true(__LINE__, !(expr), __VA_ARGS__)) return

#define assert_eq(expected, actual)\
  if (__ccut_assert_ll_eq(__LINE__, (long long)(expected), (long long)(actual))) return

#define assert_neq(expected, actual)\
  if (__ccut_assert_ll_neq(__LINE__, (long long)(expected), (long long)(actual))) return

// Can we use __typeof__(expected) __ccut_expected ?
// Not good, array types like __typeof__(char[]) will be broken.
#define assert_eqf(expected, actual, eq_fn, inspect_fn) do { \
  void* __ccut_expected = (void*)(expected); \
  void* __ccut_actual = (void*)(actual); \
  if (__ccut_assert_truef(__LINE__, eq_fn(__ccut_expected, __ccut_actual), (void*)__ccut_expected, (void*)__ccut_actual, inspect_fn)) return; \
} while(0)

#define assert_neqf(expected, actual, eq_fn, inspect_fn) do { \
  void* __ccut_expected = (void*)(expected); \
  void* __ccut_actual = (void*)(actual); \
  if (__ccut_assert_falsef(__LINE__, eq_fn(__ccut_expected, __ccut_actual), (void*)__ccut_expected, (void*)__ccut_actual, inspect_fn)) return; \
} while(0)
