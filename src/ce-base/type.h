#pragma once

#include "str.h"

typedef struct {
  usize size;
  usize align;
  str name;
  void (*drop)(void **);
  void (*copy)(void *, void const *);
  void (*move)(void *, void *);
} ce_type;

#define ce_reflect(T)                                                          \
  (ce_type) { sizeof(T), alignof(T), _s(#T), #T##_drop, #T##_copy, #T##_move }

#define ce_cleanup(T) __attribute__((cleanup(T##_drop))) T
