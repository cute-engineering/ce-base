#pragma once

#define ce_array_len(ARR) (sizeof(ARR) / sizeof(ARR[0]))

/* --- Concat --------------------------------------------------------------- */

#define __ce_concat(LHS, RHS) LHS##RHS

#define ce_concat(LHS, RHS) __ce_concat(LHS, RHS)

/* --- Stringify ------------------------------------------------------------ */

#define __ce_stringify(SYM) #SYM

#define ce_stringify(SYM) __ce_stringify(SYM)

/* --- Count ---------------------------------------------------------------- */

#define __ce_count(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_,      \
                   _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, \
                   _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, \
                   _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, \
                   _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, \
                   _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, \
                   _66, _67, _68, _69, _70, count, ...)                        \
  count

#define ce_count(__args...)                                                    \
  __ce_count(0, ##__args, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58,  \
             57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42,   \
             41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,   \
             25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,   \
             9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

/* --- Eval ----------------------------------------------------------------- */

#define __ce_eval0(...) __VA_ARGS__
#define __ce_eval1(...) __ce_eval0(__ce_eval0(__ce_eval0(__VA_ARGS__)))
#define __ce_eval2(...) __ce_eval1(__ce_eval1(__ce_eval1(__VA_ARGS__)))
#define __ce_eval3(...) __ce_eval2(__ce_eval2(__ce_eval2(__VA_ARGS__)))
#define __ce_eval4(...) __ce_eval3(__ce_eval3(__ce_eval3(__VA_ARGS__)))

#define ce_eval(...) __ce_eval4(__ce_eval4(__ce_eval4(__VA_ARGS__)))

/* --- Map ------------------------------------------------------------------ */

#define __MAP_END__(...)
#define __MAP_OUT__
#define __MAP_COMMA__ ,

#define __mapGetEnd2() 0, __MAP_END__
#define __mapGetEnd1(...) __mapGetEnd2
#define __mapGetEnd(...) __mapGetEnd1

#define __mapNext0(test, next, ...) next __MAP_OUT__
#define __mapNext1(test, next) __mapNext0(test, next, 0)
#define __mapNext(test, next) __mapNext1(__mapGetEnd test, next)

#define __map0(f, x, peek, ...)                                                \
  f(x) __mapNext(peek, __map1)(f, peek, __VA_ARGS__)
#define __map1(f, x, peek, ...)                                                \
  f(x) __mapNext(peek, __map0)(f, peek, __VA_ARGS__)

#define __ce_map_listNext1(test, next) __mapNext0(test, __MAP_COMMA__ next, 0)
#define __ce_map_listNext(test, next) __ce_map_listNext1(__mapGetEnd test, next)

#define __ce_map_list0(f, x, peek, ...)                                        \
  f(x) __ce_map_listNext(peek, __ce_map_list1)(f, peek, __VA_ARGS__)
#define __ce_map_list1(f, x, peek, ...)                                        \
  f(x) __ce_map_listNext(peek, __ce_map_list0)(f, peek, __VA_ARGS__)

// Applies the function macro `f` to each of the remaining parameters.
#define ce_map(f, ...)                                                         \
  ce_eval(__map1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

// Applies the function macro `f` to each of the remaining parameters and
// inserts commas between the results.
#define ce_map_list(f, ...)                                                    \
  ce_eval(__ce_map_list1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
