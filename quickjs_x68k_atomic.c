#include <stdbool.h>

// GCCが要求するアトミック関数の実体を定義（シングルコア環境のため単純な代入・評価）
#define ATOMIC_FUNC_OP(n, type) \
    type __atomic_fetch_add_##n(volatile void *p, type v, int m) { type old = *(volatile type *)p; *(volatile type *)p += v; return old; } \
    type __atomic_fetch_sub_##n(volatile void *p, type v, int m) { type old = *(volatile type *)p; *(volatile type *)p -= v; return old; } \
    type __atomic_fetch_and_##n(volatile void *p, type v, int m) { type old = *(volatile type *)p; *(volatile type *)p &= v; return old; } \
    type __atomic_fetch_or_##n(volatile void *p, type v, int m) { type old = *(volatile type *)p; *(volatile type *)p |= v; return old; } \
    type __atomic_fetch_xor_##n(volatile void *p, type v, int m) { type old = *(volatile type *)p; *(volatile type *)p ^= v; return old; } \
    type __atomic_exchange_##n(volatile void *p, type v, int m) { type old = *(volatile type *)p; *(volatile type *)p = v; return old; } \
    bool __atomic_compare_exchange_##n(volatile void *p, void *exp, type des, bool weak, int succ, int fail) { \
        if (*(volatile type *)p == *(type *)exp) { *(volatile type *)p = des; return true; } \
        else { *(type *)exp = *(volatile type *)p; return false; } \
    }

ATOMIC_FUNC_OP(1, unsigned char)
ATOMIC_FUNC_OP(2, unsigned short)
ATOMIC_FUNC_OP(4, unsigned long)
ATOMIC_FUNC_OP(8, unsigned long long)

unsigned long long __atomic_load_8(const volatile void *p, int m) { return *(const volatile unsigned long long *)p; }
void __atomic_store_8(volatile void *p, unsigned long long v, int m) { *(volatile unsigned long long *)p = v; }
