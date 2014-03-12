/**
Copyright (c) 2013, http://github.com/luikore/ccut
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

//// main specific

void __ccut_run_suite(const char* sname, void (*s)());
#define ccut_run_suite(__suite)\
  __ccut_run_suite(#__suite, __suite)

void __ccut_print_stats();
#define ccut_print_stats()\
  __ccut_print_stats()

//// suite specific

int __ccut_dispatch(const char* c);
#define test(c)\
  if (__ccut_dispatch(#c))

int __ccut_pending(int line);
#define pending\
  if (__ccut_pending(__LINE__)) return

int __ccut_fail(int line);
#define fail\
  if (__ccut_fail(__LINE__)) return

// NOTE since we don't care the type of expr, we use !! to turn it into int
int __ccut_assert_true(int line, int expr, const char* msg, ...);
#define assert_true(expr, ...)\
  if (__ccut_assert_true(__LINE__, !!(expr), __VA_ARGS__)) return

#define assert_false(expr, ...)\
  if (__ccut_assert_true(__LINE__, !(expr), __VA_ARGS__)) return

// NOTE if we implement this macro with a call to assert_true, expressions could be calculated twice
int __ccut_assert_ptr_eq(int line, void* expected, void* actual);
int __ccut_assert_ll_eq(int line, long long expected, long long actual);
#define assert_eq(expected, actual)\
  if (_Generic((expected), void*: __ccut_assert_ptr_eq, default: __ccut_assert_ll_eq)(__LINE__, expected, actual)) return

int __ccut_assert_ptr_neq(int line, void* expected, void* actual);
int __ccut_assert_ll_neq(int line, long long expected, long long actual);
#define assert_neq(expected, actual)\
  if (_Generic((expected), void*: __ccut_assert_ptr_neq, default: __ccut_assert_ll_neq)(__LINE__, expected, actual)) return

int __ccut_assert_str_eq(int line, const char* expected, const char* actual);
#define assert_str_eq(expected, actual)\
  if (__ccut_assert_str_eq(line, expected, actual)) return

int __ccut_assert_str_neq(int line, const char* expected, const char* actual);
#define assert_str_neq(expected, actual)\
  if (__ccut_assert_str_neq(line, expected, actual)) return

int __ccut_assert_ull_eq(int line, unsigned long long expected, unsigned long long actual);
#define assert_ull_eq(expected, actual)\
  if (__ccut_assert_ull_eq(__LINE__, expected, actual)) return

int __ccut_assert_ull_neq(int line, unsigned long long expected, unsigned long long actual);
#define assert_ull_neq(expected, actual)\
  if (__ccut_assert_ull_neq(__LINE__, expected, actual)) return

int __ccut_assert_mem_eq(int line, void* expected, void* actual, size_t size);
#define assert_mem_eq(expected, actual, size)\
  if (__ccut_assert_mem_eq(__LINE__, expected, actual, size)) return

int __ccut_assert_mem_neq(int line, void* expected, void* actual, size_t size);
#define assert_mem_neq(expected, actual, size)\
  if (__ccut_assert_mem_neq(__LINE__, expected, actual, size)) return

int __ccut_assert_eps_eq(int line, long double expected, long double actual, long double eps);
#define assert_eps_eq(expected, actual, eps)\
  if (__ccut_assert_eps_eq(__LINE__, expected, actual, eps)) return

int __ccut_assert_eps_neq(int line, long double expected, long double actual, long double eps);
#define assert_eps_neq(expected, actual, eps)\
  if (__ccut_assert_eps_neq(__LINE__, expected, actual, eps)) return
