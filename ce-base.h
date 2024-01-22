#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- Keywords ------------------------------------------------------------- */

#define ce_nil ((void *)0)

#define ce_let __auto_type const

#define ce_var __auto_type

#define ce_typeof(EXPR) __typeof__(EXPR)

#define ce_inline static inline __attribute__((always_inline))

#define ce_overload __attribute__((overloadable))

#define ce_static_cast(T, V) ((T)(V))

// clang-format off
#define ce_union_cast(T, V) ((union { T _t; ce_typeof(V) _v; }){._v = (V)}._t)
// clang-format on

/* --- Primitives ----------------------------------------------------------- */

typedef uint8_t ce_sym[];

typedef size_t ce_usize;
typedef ptrdiff_t ce_isize;

typedef uint8_t ce_u8;
typedef int8_t ce_i8;

typedef uint16_t ce_u16;
typedef int16_t ce_i16;

typedef uint32_t ce_u32;
typedef int32_t ce_i32;

typedef uint64_t ce_u64;
typedef int64_t ce_i64;

#ifdef __SIZEOF_INT128__
typedef __uint128_t ce_u128;
#endif

#ifdef __SIZEOF_INT128__
typedef __int128_t ce_i128;
#endif

typedef __fp16 ce_f16;
typedef float ce_f32;
typedef double ce_f64;
typedef long double ce_f128;

/* --- Buffers -------------------------------------------------------------- */

typedef struct
{
    ce_usize len;
    ce_u8 *ptr;
} ce_buffer;

typedef struct
{
    ce_usize len;
    ce_u8 const *ptr;
} ce_buf;

typedef struct
{
    ce_usize len;
    char const *ptr;
} ce_str;

#define ce_lit(STR) ((ce_str){sizeof(STR) - 1, STR})

typedef char const *ce_cstr;

/* --- Error and Result ----------------------------------------------------- */

typedef enum
{
    CE_OK,
#define ERR(name, ...) CE_##name,
#include "ce-err.inc"
#undef ERR
} ce_res_typ;

typedef struct
{
    ce_res_typ typ;

    union
    {
        void *pval;
        ce_u64 valu;
        ce_i64 vali;
        ce_f64 valf;
    };
} ce_res;

ce_inline ce_res ce_err(ce_res_typ typ)
{
    return (ce_res){typ, .pval = ce_nil};
}

ce_inline ce_res ce_ok() { return (ce_res){CE_OK, .pval = ce_nil}; }

ce_inline ce_res ce_okp(void *pval) { return (ce_res){CE_OK, .pval = pval}; }

ce_inline ce_res ce_oku(ce_u64 uval) { return (ce_res){CE_OK, .valu = uval}; }

ce_inline ce_res ce_oki(ce_i64 ival) { return (ce_res){CE_OK, .vali = ival}; }

ce_inline ce_res ce_okf(ce_f64 fval) { return (ce_res){CE_OK, .valf = fval}; }

#define ce_try(expr)            \
    ({                          \
        ce_res _res = (expr);   \
        if (_res.type != CE_OK) \
        {                       \
            return _res;        \
        }                       \
        _res;                   \
    })

/* --- Ordering ------------------------------------------------------------- */

typedef enum
{
    ce_less = -1,
    ce_equal = 0,
    ce_greater = 1,
} ce_ordr;
