// XFAIL: *
// FIXME: https://code.google.com/p/thread-sanitizer/issues/detail?id=29
// RUN: %clangxx_tsan -O1 %s -o %t
// RUN: TSAN_OPTIONS=allocator_may_return_null=1 %t 2>&1 | FileCheck %s
#include <stdio.h>
#include <stdlib.h>

int main() {
  void *p = malloc((size_t)-1);
  if (p != 0)
    printf("FAIL malloc(-1) = %p\n", p);
  p = malloc((size_t)-1 / 2);
  if (p != 0)
    printf("FAIL malloc(-1/2) = %p\n", p);
  p = calloc((size_t)-1, (size_t)-1);
  if (p != 0)
    printf("FAIL calloc(-1, -1) = %p\n", p);
  p = calloc((size_t)-1 / 2, (size_t)-1 / 2);
  if (p != 0)
    printf("FAIL calloc(-1/2, -1/2) = %p\n", p);
  printf("OK\n");
}

// CHECK-NOT: FAIL
// CHECK-NOT: failed to allocate
