#pragma once

#include "std.h"

typedef uint8_t sym[];

typedef size_t usize;
typedef ptrdiff_t isize;

typedef uint8_t u8;
typedef int8_t i8;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint32_t u32;
typedef int32_t i32;

typedef uint64_t u64;
typedef int64_t i64;

#ifdef __SIZEOF_INT128__
typedef __uint128_t u128;
#endif

#ifdef __SIZEOF_INT128__
typedef __int128_t i128;
#endif

typedef __fp16 f16;
typedef float f32;
typedef double f64;
typedef long double f128;
