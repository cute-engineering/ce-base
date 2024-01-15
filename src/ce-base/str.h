#pragma once

#include "ordr.h"
#include "types.h"

typedef struct {
  u8 const *buf;
  usize len;
} str;

#define _s(s) ((str){(u8 const *)(s), sizeof(s) - 1})

typedef u8 const *cstr;

static inline bool ce_str_eq(str a, str b) {
  if (a.len != b.len)
    return false;
  for (usize i = 0; i < a.len; ++i) {
    if (a.buf[i] != b.buf[i])
      return false;
  }
  return true;
}

static inline ce_ordr ce_str_cmp(str a, str b) {
  usize const len = a.len < b.len ? a.len : b.len;
  for (usize i = 0; i < len; ++i) {
    if (a.buf[i] < b.buf[i])
      return ce_less;
    if (a.buf[i] > b.buf[i])
      return ce_greater;
  }
  if (a.len < b.len)
    return ce_less;
  if (a.len > b.len)
    return ce_greater;
  return ce_equal;
}

static inline ce_ordr ce_str_cmp_fn(str const *a, str const *b) {
  return ce_str_cmp(*a, *b);
}

static inline bool ce_str_starts_with(str a, str b) {
  if (a.len < b.len)
    return false;
  for (usize i = 0; i < b.len; ++i) {
    if (a.buf[i] != b.buf[i])
      return false;
  }
  return true;
}

static inline bool ce_str_ends_with(str a, str b) {
  if (a.len < b.len)
    return false;
  for (usize i = 0; i < b.len; ++i) {
    if (a.buf[a.len - b.len + i] != b.buf[i])
      return false;
  }
  return true;
}

static inline str ce_str_contains(str a, str b) {
  if (a.len < b.len)
    return (str){0};
  for (usize i = 0; i < a.len - b.len; ++i) {
    if (ce_str_starts_with((str){a.buf + i, a.len - i}, b))
      return (str){a.buf + i, a.len - i};
  }
  return (str){0};
}
