#pragma once

#include "auto.h"
#include "std.h"

#define ce_try(EXPR)                                                           \
  ({                                                                           \
    ce_auto __expr = (EXPR);                                                   \
    if (!__ce_try_truth(__expr))                                               \
      return __ce_try_unwrap_err(&__expr);                                     \
    __ce_try_unwrap_ok(&__expr)                                                \
  })
