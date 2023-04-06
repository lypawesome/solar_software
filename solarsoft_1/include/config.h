#pragma once

#if !(defined(_MSC_VER) && !defined(__clang__))
    #define PURE_FUNCTION __attribute__((pure))
    #define LIKELY(expr) __builtin_expect(!!(expr), true)
    #define UNLIKELY(expr) __builtin_expect(!!(expr), false)
    #define NO_RETURNS_ALIAS __attribute__((malloc))
#else
    #define PURE_FUNCTION __declspec(noalias)
    #define LIKELY(expr) (expr)
    #define UNLIKELY(expr) (expr)
    #define NO_RETURNS_ALIAS __declspec(restrict)
#endif
