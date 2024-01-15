#pragma once

#include "auto.h"

#define ce_static_cast(T, V) ((T)(V))

#define ce_union_cast(T, V)                                                    \
  ((union {                                                                    \
     ce_typeof(V) __v;                                                         \
     T __t;                                                                    \
   }){.__v = (V)}                                                              \
       .__t)
