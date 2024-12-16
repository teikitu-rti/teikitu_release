// atomic standard header

// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once
#ifndef _ATOMIC_
#define _ATOMIC_
#include <yvals.h>
#if _STL_COMPILER_PREPROCESSOR

#ifdef _M_CEE_PURE
#error <atomic> is not supported when compiling with /clr:pure.
#endif // _M_CEE_PURE

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <xatomic.h>
#if _HAS_CXX20
#include <xatomic_wait.h>
#endif // _HAS_CXX20
#include <xthreads.h>

#pragma pack(push, _CRT_PACKING)
#pragma warning(push, _STL_WARNING_LEVEL)
#pragma warning(disable : _STL_DISABLED_WARNINGS)
_STL_DISABLE_CLANG_WARNINGS
#pragma push_macro("new")
#undef new

#define _Compiler_barrier() _STL_DISABLE_DEPRECATED_WARNING _ReadWriteBarrier() _STL_RESTORE_DEPRECATED_WARNING

#if defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
#define _Memory_barrier()             __dmb(0xB) // inner shared data memory barrier
#define _Compiler_or_memory_barrier() _Memory_barrier()
#elif defined(_M_IX86) || defined(_M_X64)
// x86/x64 hardware only emits memory barriers inside _Interlocked intrinsics
#define _Compiler_or_memory_barrier() _Compiler_barrier()
#else // ^^^ x86/x64 / unsupported hardware vvv
#error Unsupported hardware
#endif // hardware

#ifndef _INVALID_MEMORY_ORDER
#ifdef _DEBUG
#define _INVALID_MEMORY_ORDER _STL_REPORT_ERROR("Invalid memory order")
#else // ^^^ _DEBUG / !_DEBUG vvv
#define _INVALID_MEMORY_ORDER
#endif // _DEBUG
#endif // _INVALID_MEMORY_ORDER

#ifdef _WIN64
#if _STD_ATOMIC_ALWAYS_USE_CMPXCHG16B == 1
#define _STD_COMPARE_EXCHANGE_128 _InterlockedCompareExchange128
#else // ^^^ _STD_ATOMIC_ALWAYS_USE_CMPXCHG16B == 1 // _STD_ATOMIC_ALWAYS_USE_CMPXCHG16B == 0 vvv
// 16-byte atomics are separately compiled for x64, as not all x64 hardware has the cmpxchg16b
// instruction; in the event this instruction is not available, the fallback is a global
// synchronization object shared by all 16-byte atomics.
// (Note: machines without this instruction typically have 2 cores or fewer, so this isn't too bad)
// All pointer parameters must be 16-byte aligned.
extern "C" _NODISCARD unsigned char __stdcall __std_atomic_compare_exchange_128(
    _Inout_bytecount_(16) long long* _Destination, _In_ long long _ExchangeHigh, _In_ long long _ExchangeLow,
    _Inout_bytecount_(16) long long* _ComparandResult) noexcept;
extern "C" _NODISCARD char __stdcall __std_atomic_has_cmpxchg16b() noexcept;
#define _STD_COMPARE_EXCHANGE_128 __std_atomic_compare_exchange_128
#endif // _STD_ATOMIC_ALWAYS_USE_CMPXCHG16B == 1
#endif // _WIN64

// Controls whether atomic::is_always_lock_free triggers for sizeof(void *) or 2 * sizeof(void *)
#if _STD_ATOMIC_ALWAYS_USE_CMPXCHG16B == 1 || !defined(_M_X64) || defined(_M_ARM64EC)
#define _ATOMIC_HAS_DCAS 1
#else // ^^^ We always have DCAS / We only sometimes have DCAS vvv
#define _ATOMIC_HAS_DCAS 0
#endif // _STD_ATOMIC_ALWAYS_USE_CMPXCHG16B == 1 || !defined(_M_X64) || defined(_M_ARM64EC)

#if defined(_M_IX86) || (defined(_M_X64) && !defined(_M_ARM64EC))
#define _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _Intrinsic, ...) \
    _Check_memory_order(_Order);                                   \
    _Result = _Intrinsic(__VA_ARGS__)
#elif defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
#define _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _Intrinsic, ...) \
    switch (_Order) {                                              \
    case memory_order_relaxed:                                     \
        _Result = _INTRIN_RELAXED(_Intrinsic)(__VA_ARGS__);        \
        break;                                                     \
    case memory_order_consume:                                     \
    case memory_order_acquire:                                     \
        _Result = _INTRIN_ACQUIRE(_Intrinsic)(__VA_ARGS__);        \
        break;                                                     \
    case memory_order_release:                                     \
        _Result = _INTRIN_RELEASE(_Intrinsic)(__VA_ARGS__);        \
        break;                                                     \
    default:                                                       \
        _INVALID_MEMORY_ORDER;                                     \
        /* [[fallthrough]]; */                                     \
    case memory_order_acq_rel:                                     \
    case memory_order_seq_cst:                                     \
        _Result = _Intrinsic(__VA_ARGS__);                         \
        break;                                                     \
    }
#endif // hardware

#define ATOMIC_BOOL_LOCK_FREE 2
#define ATOMIC_CHAR_LOCK_FREE 2
#ifdef __cpp_lib_char8_t
#define ATOMIC_CHAR8_T_LOCK_FREE 2
#endif // __cpp_lib_char8_t
#define ATOMIC_CHAR16_T_LOCK_FREE 2
#define ATOMIC_CHAR32_T_LOCK_FREE 2
#define ATOMIC_WCHAR_T_LOCK_FREE  2
#define ATOMIC_SHORT_LOCK_FREE    2
#define ATOMIC_INT_LOCK_FREE      2
#define ATOMIC_LONG_LOCK_FREE     2
#define ATOMIC_LLONG_LOCK_FREE    2
#define ATOMIC_POINTER_LOCK_FREE  2

_EXTERN_C
_Smtx_t* __stdcall __std_atomic_get_mutex(const void* _Key) noexcept;
_END_EXTERN_C
// Padding bits should not participate in cmpxchg comparison starting in C++20.
// Clang does not have __builtin_zero_non_value_bits to exclude these bits to implement this C++20 feature.
// The EDG front-end substitutes everything and runs into incomplete types passed to atomic<T>.
#if _HAS_CXX20 && !defined(__clang__) /* TRANSITION, LLVM-46685 */ && !defined(__EDG__)
#define _CMPXCHG_MASK_OUT_PADDING_BITS 1
#else
#define _CMPXCHG_MASK_OUT_PADDING_BITS 0
#endif

_STD_BEGIN
#if _CMPXCHG_MASK_OUT_PADDING_BITS
struct _Form_mask_t {};
_INLINE_VAR constexpr _Form_mask_t _Form_mask{};
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS

template <class _Ty>
struct _Storage_for {
    // uninitialized space to store a _Ty
    alignas(_Ty) unsigned char _Storage[sizeof(_Ty)];

    _Storage_for()                    = default;
    _Storage_for(const _Storage_for&) = delete;
    _Storage_for& operator=(const _Storage_for&) = delete;

#if _CMPXCHG_MASK_OUT_PADDING_BITS
    explicit _Storage_for(_Form_mask_t) noexcept {
        _CSTD memset(_Storage, 0xff, sizeof(_Ty));
        __builtin_zero_non_value_bits(_Ptr());
    }
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS

    _NODISCARD _Ty& _Ref() noexcept {
        return reinterpret_cast<_Ty&>(_Storage);
    }

    _NODISCARD _Ty* _Ptr() noexcept {
        return reinterpret_cast<_Ty*>(&_Storage);
    }
};

#if _CMPXCHG_MASK_OUT_PADDING_BITS
template <class _Ty>
inline constexpr bool _Might_have_non_value_bits =
    !has_unique_object_representations_v<_Ty> && !is_floating_point_v<_Ty>;
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS

extern "C" inline void atomic_thread_fence(const memory_order _Order) noexcept {
    if (_Order == memory_order_relaxed) {
        return;
    }

#if defined(_M_IX86) || (defined(_M_X64) && !defined(_M_ARM64EC))
    _Compiler_barrier();
    if (_Order == memory_order_seq_cst) {
        volatile long _Guard; // Not initialized to avoid an unnecessary operation; the value does not matter

        // _mm_mfence could have been used, but it is not supported on older x86 CPUs and is slower on some recent CPUs.
        // The memory fence provided by interlocked operations has some exceptions, but this is fine:
        // std::atomic_thread_fence works with respect to other atomics only; it may not be a full fence for all ops.
#pragma warning(suppress : 6001) // "Using uninitialized memory '_Guard'"
#pragma warning(suppress : 28113) // "Accessing a local variable _Guard via an Interlocked function: This is an unusual
                                  // usage which could be reconsidered."
        (void) _InterlockedIncrement(&_Guard);
        _Compiler_barrier();
    }
#elif defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
    _Memory_barrier();
#else // ^^^ ARM32/ARM64/ARM64EC / unsupported hardware vvv
#error Unsupported hardware
#endif // unsupported hardware
}

extern "C" inline void atomic_signal_fence(const memory_order _Order) noexcept {
    if (_Order != memory_order_relaxed) {
        _Compiler_barrier();
    }
}

template <class _Ty>
_Ty kill_dependency(_Ty _Arg) noexcept { // "magic" template that kills dependency ordering when called
    return _Arg;
}

inline void _Check_memory_order(const memory_order _Order) noexcept {
    // check that _Order is a valid memory_order
    if (static_cast<unsigned int>(_Order) > static_cast<unsigned int>(memory_order_seq_cst)) {
        _INVALID_MEMORY_ORDER;
    }
}

inline void _Check_store_memory_order(const memory_order _Order) noexcept {
    switch (_Order) {
    case memory_order_relaxed:
    case memory_order_release:
    case memory_order_seq_cst:
        // nothing to do
        break;
    case memory_order_consume:
    case memory_order_acquire:
    case memory_order_acq_rel:
    default:
        _INVALID_MEMORY_ORDER;
        break;
    }
}

inline void _Check_load_memory_order(const memory_order _Order) noexcept {
    switch (_Order) {
    case memory_order_relaxed:
    case memory_order_consume:
    case memory_order_acquire:
    case memory_order_seq_cst:
        // nothing to do
        break;
    case memory_order_release:
    case memory_order_acq_rel:
    default:
        _INVALID_MEMORY_ORDER;
        break;
    }
}

_NODISCARD inline memory_order _Combine_cas_memory_orders(
    const memory_order _Success, const memory_order _Failure) noexcept {
    // Finds upper bound of a compare/exchange memory order
    // pair, according to the following partial order:
    //     seq_cst
    //        |
    //     acq_rel
    //     /     \
    // acquire  release
    //    |       |
    // consume    |
    //     \     /
    //     relaxed
    static constexpr memory_order _Combined_memory_orders[6][6] = {// combined upper bounds
        {memory_order_relaxed, memory_order_consume, memory_order_acquire, memory_order_release, memory_order_acq_rel,
            memory_order_seq_cst},
        {memory_order_consume, memory_order_consume, memory_order_acquire, memory_order_acq_rel, memory_order_acq_rel,
            memory_order_seq_cst},
        {memory_order_acquire, memory_order_acquire, memory_order_acquire, memory_order_acq_rel, memory_order_acq_rel,
            memory_order_seq_cst},
        {memory_order_release, memory_order_acq_rel, memory_order_acq_rel, memory_order_release, memory_order_acq_rel,
            memory_order_seq_cst},
        {memory_order_acq_rel, memory_order_acq_rel, memory_order_acq_rel, memory_order_acq_rel, memory_order_acq_rel,
            memory_order_seq_cst},
        {memory_order_seq_cst, memory_order_seq_cst, memory_order_seq_cst, memory_order_seq_cst, memory_order_seq_cst,
            memory_order_seq_cst}};

    _Check_memory_order(_Success);
    _Check_load_memory_order(_Failure);
    return _Combined_memory_orders[static_cast<int>(_Success)][static_cast<int>(_Failure)];
}

template <class _Integral, class _Ty>
_NODISCARD _Integral _Atomic_reinterpret_as(const _Ty& _Source) noexcept {
    // interprets _Source as the supplied integral type
    static_assert(is_integral_v<_Integral>, "Tried to reinterpret memory as non-integral");
    if constexpr (is_integral_v<_Ty> && sizeof(_Integral) == sizeof(_Ty)) {
        return static_cast<_Integral>(_Source);
    } else if constexpr (is_pointer_v<_Ty> && sizeof(_Integral) == sizeof(_Ty)) {
        return reinterpret_cast<_Integral>(_Source);
    } else {
        _Integral _Result{}; // zero padding bits
        _CSTD memcpy(&_Result, _STD addressof(_Source), sizeof(_Source));
        return _Result;
    }
}

inline void _Load_barrier(const memory_order _Order) noexcept { // implement memory barrier for atomic load functions
    _Check_load_memory_order(_Order);
    if (_Order != memory_order_relaxed) {
        _Compiler_or_memory_barrier();
    }
}

#if 1 // TRANSITION, ABI
template <class _Ty>
struct _Atomic_padded {
    alignas(sizeof(_Ty)) mutable _Ty _Value; // align to sizeof(T); x86 stack aligns 8-byte objects on 4-byte boundaries
};

#else // ^^^ don't break ABI / break ABI vvv
template <class _Ty>
struct _Atomic_storage_traits { // properties for how _Ty is stored in an atomic
    static constexpr size_t _Storage_size = sizeof(_Ty) == 1  ? 1
                                          : sizeof(_Ty) == 2  ? 2
                                          : sizeof(_Ty) <= 4  ? 4
                                          : sizeof(_Ty) <= 8  ? 8
#if defined(_M_X64) || defined(_M_ARM64) || defined(_M_ARM64EC)
                                          : sizeof(_Ty) <= 16 ? 16
#endif // 64 bits
                                                              : sizeof(_Ty);

    static constexpr size_t _Padding_size = _Storage_size - sizeof(_Ty);
    static constexpr bool _Uses_padding   = _Padding_size != 0;
};

template <class _Ty>
struct _Atomic_storage_traits<_Ty&> { // properties for how _Ty is stored in an atomic_ref
    static constexpr size_t _Storage_size = sizeof(_Ty);
    static constexpr bool _Uses_padding   = false;
};

template <class _Ty, bool = _Atomic_storage_traits<_Ty>::_Uses_padding>
struct _Atomic_padded { // aggregate to allow explicit constexpr zeroing of padding
    alignas(_Atomic_storage_traits<_Ty>::_Storage_size) mutable _Ty _Value;
    mutable unsigned char _Padding[_Atomic_storage_traits<_Ty>::_Padding_size];
};

template <class _Ty>
struct _Atomic_padded<_Ty, false> {
    alignas(sizeof(_Ty)) mutable _Ty _Value; // align to sizeof(T); x86 stack aligns 8-byte objects on 4-byte boundaries
};

template <class _Ty>
struct _Atomic_padded<_Ty&, false> {
    _Ty& _Value;
};

#endif // TRANSITION, ABI

template <class _Ty>
struct _Atomic_storage_types {
    using _TStorage = _Atomic_padded<_Ty>;
    using _Spinlock = long;
};

template <class _Ty>
struct _Atomic_storage_types<_Ty&> {
    using _TStorage = _Ty&;
    using _Spinlock = _Smtx_t*; // POINTER TO mutex
};

#if 1 // TRANSITION, ABI
template <class _Ty, size_t = sizeof(remove_reference_t<_Ty>)>
#else // ^^^ don't break ABI / break ABI vvv
template <class _Ty, size_t = _Atomic_storage_traits<_Ty>::_Storage_size>
#endif // TRANSITION, ABI
struct _Atomic_storage;

#if _HAS_CXX20
template <class _Ty, class _Value_type>
void _Atomic_wait_direct(
    const _Atomic_storage<_Ty>* const _This, _Value_type _Expected_bytes, const memory_order _Order) noexcept {
    const auto _Storage_ptr = _STD addressof(_This->_Storage);
    for (;;) {
        const _Value_type _Observed_bytes = _Atomic_reinterpret_as<_Value_type>(_This->load(_Order));
        if (_Expected_bytes != _Observed_bytes) {
#if _CMPXCHG_MASK_OUT_PADDING_BITS
            using _TVal = remove_reference_t<_Ty>;
            if constexpr (_Might_have_non_value_bits<_TVal>) {
                _Storage_for<_TVal> _Mask{_Form_mask};
                const _Value_type _Mask_val = _Atomic_reinterpret_as<_Value_type>(_Mask._Ref());

                if (((_Expected_bytes ^ _Observed_bytes) & _Mask_val) == 0) {
                    _Expected_bytes = _Observed_bytes;
                    continue;
                }
            }
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS

            return;
        }

        __std_atomic_wait_direct(_Storage_ptr, &_Expected_bytes, sizeof(_Value_type), _Atomic_wait_no_timeout);
    }
}
#endif // _HAS_CXX20

#if 1 // TRANSITION, ABI, GH-1151
inline void _Atomic_lock_acquire(long& _Spinlock) noexcept {
#if defined(_M_IX86) || (defined(_M_X64) && !defined(_M_ARM64EC))
    // Algorithm from Intel(R) 64 and IA-32 Architectures Optimization Reference Manual, May 2020
    // Example 2-4. Contended Locks with Increasing Back-off Example - Improved Version, page 2-22
    // The code in mentioned manual is covered by the 0BSD license.
    int _Current_backoff   = 1;
    const int _Max_backoff = 64;
    while (_InterlockedExchange(&_Spinlock, 1) != 0) {
        while (__iso_volatile_load32(&reinterpret_cast<int&>(_Spinlock)) != 0) {
            for (int _Count_down = _Current_backoff; _Count_down != 0; --_Count_down) {
                _mm_pause();
            }
            _Current_backoff = _Current_backoff < _Max_backoff ? _Current_backoff << 1 : _Max_backoff;
        }
    }
#elif defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
    while (_InterlockedExchange(&_Spinlock, 1) != 0) { // TRANSITION, GH-1133: _InterlockedExchange_acq
        while (__iso_volatile_load32(&reinterpret_cast<int&>(_Spinlock)) != 0) {
            __yield();
        }
    }
#else // ^^^ defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC) ^^^
#error Unsupported hardware
#endif
}

inline void _Atomic_lock_release(long& _Spinlock) noexcept {
#if defined(_M_IX86) || (defined(_M_X64) && !defined(_M_ARM64EC))
    _InterlockedExchange(&_Spinlock, 0); // TRANSITION, GH-1133: same as ARM
#elif defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
    _Memory_barrier();
    __iso_volatile_store32(reinterpret_cast<int*>(&_Spinlock), 0);
    _Memory_barrier(); // TRANSITION, GH-1133: remove
#else // ^^^ defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC) ^^^
#error Unsupported hardware
#endif
}

inline void _Atomic_lock_acquire(_Smtx_t* _Spinlock) noexcept {
    _Smtx_lock_exclusive(_Spinlock);
}

inline void _Atomic_lock_release(_Smtx_t* _Spinlock) noexcept {
    _Smtx_unlock_exclusive(_Spinlock);
}

template <class _Spinlock_t>
class _NODISCARD _Atomic_lock_guard {
public:
    explicit _Atomic_lock_guard(_Spinlock_t& _Spinlock_) noexcept : _Spinlock(_Spinlock_) {
        _Atomic_lock_acquire(_Spinlock);
    }

    ~_Atomic_lock_guard() {
        _Atomic_lock_release(_Spinlock);
    }

    _Atomic_lock_guard(const _Atomic_lock_guard&) = delete;
    _Atomic_lock_guard& operator=(const _Atomic_lock_guard&) = delete;

private:
    _Spinlock_t& _Spinlock;
};

#if _HAS_CXX20
template <class _Spinlock_t>
bool __stdcall _Atomic_wait_compare_non_lock_free(
    const void* _Storage, void* _Comparand, size_t _Size, void* _Spinlock_raw) noexcept {
    _Spinlock_t& _Spinlock = *static_cast<_Spinlock_t*>(_Spinlock_raw);
    _Atomic_lock_acquire(_Spinlock);
    const auto _Cmp_result = _CSTD memcmp(_Storage, _Comparand, _Size);
    _Atomic_lock_release(_Spinlock);
    return _Cmp_result == 0;
}

#ifdef _WIN64
inline bool __stdcall _Atomic_wait_compare_16_bytes(const void* _Storage, void* _Comparand, size_t, void*) noexcept {
    const auto _Dest              = static_cast<long long*>(const_cast<void*>(_Storage));
    const auto _Cmp               = static_cast<const long long*>(_Comparand);
    alignas(16) long long _Tmp[2] = {_Cmp[0], _Cmp[1]};
#if defined(_M_X64) && !defined(_M_ARM64EC)
    return _STD_COMPARE_EXCHANGE_128(_Dest, _Tmp[1], _Tmp[0], _Tmp) != 0;
#else // ^^^ _M_X64 / ARM64, _M_ARM64EC vvv
    return _InterlockedCompareExchange128_nf(_Dest, _Tmp[1], _Tmp[0], _Tmp) != 0;
#endif // ^^^ ARM64, _M_ARM64EC ^^^
}
#endif // _WIN64
#endif // _HAS_CXX20
#endif // TRANSITION, ABI

template <class _Ty, size_t /* = ... */>
struct _Atomic_storage {
    // Provides operations common to all specializations of std::atomic, load, store, exchange, and CAS.
    // Locking version used when hardware has no atomic operations for sizeof(_Ty).

    using _TVal  = remove_reference_t<_Ty>;
    using _Guard = _Atomic_lock_guard<typename _Atomic_storage_types<_Ty>::_Spinlock>;

    _Atomic_storage() = default;

    /* implicit */ constexpr _Atomic_storage(conditional_t<is_reference_v<_Ty>, _Ty, const _TVal> _Value) noexcept
        : _Storage(_Value) {
        // non-atomically initialize this atomic
    }

    void store(const _TVal _Value, const memory_order _Order = memory_order_seq_cst) noexcept {
        // store with sequential consistency
        _Check_store_memory_order(_Order);
        _Guard _Lock{_Spinlock};
        _Storage = _Value;
    }

    _NODISCARD _TVal load(const memory_order _Order = memory_order_seq_cst) const noexcept {
        // load with sequential consistency
        _Check_load_memory_order(_Order);
        _Guard _Lock{_Spinlock};
        _TVal _Local(_Storage);
        return _Local;
    }

    _TVal exchange(const _TVal _Value, const memory_order _Order = memory_order_seq_cst) noexcept {
        // exchange _Value with _Storage with sequential consistency
        _Check_memory_order(_Order);
        _Guard _Lock{_Spinlock};
        _TVal _Result(_Storage);
        _Storage = _Value;
        return _Result;
    }

    bool compare_exchange_strong(_TVal& _Expected, const _TVal _Desired,
        const memory_order _Order = memory_order_seq_cst) noexcept { // CAS with sequential consistency, plain
        _Check_memory_order(_Order);
        const auto _Storage_ptr  = _STD addressof(_Storage);
        const auto _Expected_ptr = _STD addressof(_Expected);
        bool _Result;
#if _CMPXCHG_MASK_OUT_PADDING_BITS
        __builtin_zero_non_value_bits(_Expected_ptr);
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS
        _Guard _Lock{_Spinlock};
#if _CMPXCHG_MASK_OUT_PADDING_BITS
        if constexpr (_Might_have_non_value_bits<_TVal>) {
            _Storage_for<_TVal> _Local;
            const auto _Local_ptr = _Local._Ptr();
            _CSTD memcpy(_Local_ptr, _Storage_ptr, sizeof(_TVal));
            __builtin_zero_non_value_bits(_Local_ptr);
            _Result = _CSTD memcmp(_Local_ptr, _Expected_ptr, sizeof(_TVal)) == 0;
        } else {
            _Result = _CSTD memcmp(_Storage_ptr, _Expected_ptr, sizeof(_TVal)) == 0;
        }
#else // _CMPXCHG_MASK_OUT_PADDING_BITS
        _Result = _CSTD memcmp(_Storage_ptr, _Expected_ptr, sizeof(_TVal)) == 0;
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS
        if (_Result) {
            _CSTD memcpy(_Storage_ptr, _STD addressof(_Desired), sizeof(_TVal));
        } else {
            _CSTD memcpy(_Expected_ptr, _Storage_ptr, sizeof(_TVal));
        }

        return _Result;
    }

#if _HAS_CXX20
    void wait(_TVal _Expected, memory_order = memory_order_seq_cst) const noexcept {
        const auto _Storage_ptr  = _STD addressof(_Storage);
        const auto _Expected_ptr = _STD addressof(_Expected);
        for (;;) {
            {
                _Guard _Lock{_Spinlock};
                if (_CSTD memcmp(_Storage_ptr, _Expected_ptr, sizeof(_TVal)) != 0) {
                    // contents differed, we might be done, check for padding
#if _CMPXCHG_MASK_OUT_PADDING_BITS
                    if constexpr (_Might_have_non_value_bits<_TVal>) {
                        _Storage_for<_TVal> _Local;
                        const auto _Local_ptr = _Local._Ptr();
                        _CSTD memcpy(_Local_ptr, _Storage_ptr, sizeof(_TVal));
                        __builtin_zero_non_value_bits(_Local_ptr);
                        __builtin_zero_non_value_bits(_Expected_ptr);
                        if (_CSTD memcmp(_Local_ptr, _Expected_ptr, sizeof(_TVal)) == 0) {
                            // _Storage differs from _Expected only by padding; copy the padding from _Storage into
                            // _Expected
                            _CSTD memcpy(_Expected_ptr, _Storage_ptr, sizeof(_TVal));
                        } else {
                            // truly different, we're done
                            return;
                        }
                    } else
#endif // #if _CMPXCHG_MASK_OUT_PADDING_BITS
                    {
                        return;
                    }
                }
            } // unlock

            __std_atomic_wait_indirect(_Storage_ptr, _Expected_ptr, sizeof(_TVal), &_Spinlock,
                &_Atomic_wait_compare_non_lock_free<decltype(_Spinlock)>, _Atomic_wait_no_timeout);
        }
    }

    void notify_one() noexcept {
        __std_atomic_notify_one_indirect(_STD addressof(_Storage));
    }

    void notify_all() noexcept {
        __std_atomic_notify_all_indirect(_STD addressof(_Storage));
    }
#endif // _HAS_CXX20

#if 1 // TRANSITION, ABI
protected:
    void _Init_spinlock_for_ref() noexcept {
        _Spinlock = __std_atomic_get_mutex(_STD addressof(_Storage));
    }

private:
    // Spinlock integer for non-lock-free atomic. <xthreads.h> mutex pointer for non-lock-free atomic_ref
    mutable typename _Atomic_storage_types<_Ty>::_Spinlock _Spinlock{};

public:
    _Ty _Storage{};

#else // ^^^ don't break ABI / break ABI vvv
    _Ty _Storage;
    mutable _Smtx_t _Mutex{};
#endif // TRANSITION, ABI
};

template <class _Ty>
struct _Atomic_storage<_Ty, 1> { // lock-free using 1-byte intrinsics

    using _TVal = remove_reference_t<_Ty>;

    _Atomic_storage() = default;

    /* implicit */ constexpr _Atomic_storage(conditional_t<is_reference_v<_Ty>, _Ty, const _TVal> _Value) noexcept
        : _Storage{_Value} {
        // non-atomically initialize this atomic
    }

    void store(const _TVal _Value) noexcept { // store with sequential consistency
        const auto _Mem      = _Atomic_address_as<char>(_Storage);
        const char _As_bytes = _Atomic_reinterpret_as<char>(_Value);
#if defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
        _Memory_barrier();
        __iso_volatile_store8(_Mem, _As_bytes);
        _Memory_barrier();
#else // ^^^ ARM32/ARM64/ARM64EC hardware / x86/x64 hardware vvv
        (void) _InterlockedExchange8(_Mem, _As_bytes);
#endif // hardware
    }

    void store(const _TVal _Value, const memory_order _Order) noexcept { // store with given memory order
        const auto _Mem      = _Atomic_address_as<char>(_Storage);
        const char _As_bytes = _Atomic_reinterpret_as<char>(_Value);
        switch (_Order) {
        case memory_order_relaxed:
            __iso_volatile_store8(_Mem, _As_bytes);
            return;
        case memory_order_release:
            _Compiler_or_memory_barrier();
            __iso_volatile_store8(_Mem, _As_bytes);
            return;
        default:
        case memory_order_consume:
        case memory_order_acquire:
        case memory_order_acq_rel:
            _INVALID_MEMORY_ORDER;
            // [[fallthrough]];
        case memory_order_seq_cst:
            store(_Value);
            return;
        }
    }

    _NODISCARD _TVal load() const noexcept { // load with sequential consistency
        const auto _Mem = _Atomic_address_as<char>(_Storage);
        char _As_bytes  = __iso_volatile_load8(_Mem);
        _Compiler_or_memory_barrier();
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    _NODISCARD _TVal load(const memory_order _Order) const noexcept { // load with given memory order
        const auto _Mem = _Atomic_address_as<char>(_Storage);
        char _As_bytes  = __iso_volatile_load8(_Mem);
        _Load_barrier(_Order);
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    _TVal exchange(const _TVal _Value, const memory_order _Order = memory_order_seq_cst) noexcept {
        // exchange with given memory order
        char _As_bytes;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _As_bytes, _InterlockedExchange8, _Atomic_address_as<char>(_Storage),
            _Atomic_reinterpret_as<char>(_Value));
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    bool compare_exchange_strong(_TVal& _Expected, const _TVal _Desired,
        const memory_order _Order = memory_order_seq_cst) noexcept { // CAS with given memory order
        char _Expected_bytes = _Atomic_reinterpret_as<char>(_Expected); // read before atomic operation
        char _Prev_bytes;

#if _CMPXCHG_MASK_OUT_PADDING_BITS
        if constexpr (_Might_have_non_value_bits<_TVal>) {
            _Storage_for<_TVal> _Mask{_Form_mask};
            const char _Mask_val = _Atomic_reinterpret_as<char>(_Mask._Ref());

            for (;;) {
                _ATOMIC_CHOOSE_INTRINSIC(_Order, _Prev_bytes, _InterlockedCompareExchange8,
                    _Atomic_address_as<char>(_Storage), _Atomic_reinterpret_as<char>(_Desired), _Expected_bytes);
                if (_Prev_bytes == _Expected_bytes) {
                    return true;
                }

                if ((_Prev_bytes ^ _Expected_bytes) & _Mask_val) {
                    reinterpret_cast<char&>(_Expected) = _Prev_bytes;
                    return false;
                }
                _Expected_bytes = (_Expected_bytes & _Mask_val) | (_Prev_bytes & ~_Mask_val);
            }
        }
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Prev_bytes, _InterlockedCompareExchange8, _Atomic_address_as<char>(_Storage),
            _Atomic_reinterpret_as<char>(_Desired), _Expected_bytes);
        if (_Prev_bytes == _Expected_bytes) {
            return true;
        }

        reinterpret_cast<char&>(_Expected) = _Prev_bytes;
        return false;
    }

#if _HAS_CXX20
    void wait(const _TVal _Expected, const memory_order _Order = memory_order_seq_cst) const noexcept {
        _Atomic_wait_direct(this, _Atomic_reinterpret_as<char>(_Expected), _Order);
    }

    void notify_one() noexcept {
        __std_atomic_notify_one_direct(_STD addressof(_Storage));
    }

    void notify_all() noexcept {
        __std_atomic_notify_all_direct(_STD addressof(_Storage));
    }
#endif // _HAS_CXX20

    typename _Atomic_storage_types<_Ty>::_TStorage _Storage;
};

template <class _Ty>
struct _Atomic_storage<_Ty, 2> { // lock-free using 2-byte intrinsics

    using _TVal = remove_reference_t<_Ty>;

    _Atomic_storage() = default;

    /* implicit */ constexpr _Atomic_storage(conditional_t<is_reference_v<_Ty>, _Ty, const _TVal> _Value) noexcept
        : _Storage{_Value} {
        // non-atomically initialize this atomic
    }

    void store(const _TVal _Value) noexcept { // store with sequential consistency
        const auto _Mem       = _Atomic_address_as<short>(_Storage);
        const short _As_bytes = _Atomic_reinterpret_as<short>(_Value);
#if defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
        _Memory_barrier();
        __iso_volatile_store16(_Mem, _As_bytes);
        _Memory_barrier();
#else // ^^^ ARM32/ARM64/ARM64EC hardware / x86/x64 hardware vvv
        (void) _InterlockedExchange16(_Mem, _As_bytes);
#endif // hardware
    }

    void store(const _TVal _Value, const memory_order _Order) noexcept { // store with given memory order
        const auto _Mem       = _Atomic_address_as<short>(_Storage);
        const short _As_bytes = _Atomic_reinterpret_as<short>(_Value);
        switch (_Order) {
        case memory_order_relaxed:
            __iso_volatile_store16(_Mem, _As_bytes);
            return;
        case memory_order_release:
            _Compiler_or_memory_barrier();
            __iso_volatile_store16(_Mem, _As_bytes);
            return;
        default:
        case memory_order_consume:
        case memory_order_acquire:
        case memory_order_acq_rel:
            _INVALID_MEMORY_ORDER;
            // [[fallthrough]];
        case memory_order_seq_cst:
            store(_Value);
            return;
        }
    }

    _NODISCARD _TVal load() const noexcept { // load with sequential consistency
        const auto _Mem = _Atomic_address_as<short>(_Storage);
        short _As_bytes = __iso_volatile_load16(_Mem);
        _Compiler_or_memory_barrier();
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    _NODISCARD _TVal load(const memory_order _Order) const noexcept { // load with given memory order
        const auto _Mem = _Atomic_address_as<short>(_Storage);
        short _As_bytes = __iso_volatile_load16(_Mem);
        _Load_barrier(_Order);
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    _TVal exchange(const _TVal _Value, const memory_order _Order = memory_order_seq_cst) noexcept {
        // exchange with given memory order
        short _As_bytes;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _As_bytes, _InterlockedExchange16, _Atomic_address_as<short>(_Storage),
            _Atomic_reinterpret_as<short>(_Value));
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    bool compare_exchange_strong(_TVal& _Expected, const _TVal _Desired,
        const memory_order _Order = memory_order_seq_cst) noexcept { // CAS with given memory order
        short _Expected_bytes = _Atomic_reinterpret_as<short>(_Expected); // read before atomic operation
        short _Prev_bytes;
#if _CMPXCHG_MASK_OUT_PADDING_BITS
        if constexpr (_Might_have_non_value_bits<_Ty>) {
            _Storage_for<_TVal> _Mask{_Form_mask};
            const short _Mask_val = _Atomic_reinterpret_as<short>(_Mask._Ref());

            for (;;) {
                _ATOMIC_CHOOSE_INTRINSIC(_Order, _Prev_bytes, _InterlockedCompareExchange16,
                    _Atomic_address_as<short>(_Storage), _Atomic_reinterpret_as<short>(_Desired), _Expected_bytes);
                if (_Prev_bytes == _Expected_bytes) {
                    return true;
                }

                if ((_Prev_bytes ^ _Expected_bytes) & _Mask_val) {
                    _CSTD memcpy(_STD addressof(_Expected), &_Prev_bytes, sizeof(_TVal));
                    return false;
                }
                _Expected_bytes = (_Expected_bytes & _Mask_val) | (_Prev_bytes & ~_Mask_val);
            }
        }
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Prev_bytes, _InterlockedCompareExchange16,
            _Atomic_address_as<short>(_Storage), _Atomic_reinterpret_as<short>(_Desired), _Expected_bytes);
        if (_Prev_bytes == _Expected_bytes) {
            return true;
        }

        _CSTD memcpy(_STD addressof(_Expected), &_Prev_bytes, sizeof(_Ty));
        return false;
    }

#if _HAS_CXX20
    void wait(const _TVal _Expected, const memory_order _Order = memory_order_seq_cst) const noexcept {
        _Atomic_wait_direct(this, _Atomic_reinterpret_as<short>(_Expected), _Order);
    }

    void notify_one() noexcept {
        __std_atomic_notify_one_direct(_STD addressof(_Storage));
    }

    void notify_all() noexcept {
        __std_atomic_notify_all_direct(_STD addressof(_Storage));
    }
#endif // _HAS_CXX20

    typename _Atomic_storage_types<_Ty>::_TStorage _Storage;
};

template <class _Ty>
struct _Atomic_storage<_Ty, 4> { // lock-free using 4-byte intrinsics

    using _TVal = remove_reference_t<_Ty>;

    _Atomic_storage() = default;

    /* implicit */ constexpr _Atomic_storage(conditional_t<is_reference_v<_Ty>, _Ty, const _TVal> _Value) noexcept
        : _Storage{_Value} {
        // non-atomically initialize this atomic
    }

    void store(const _TVal _Value) noexcept { // store with sequential consistency
#if defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
        _Memory_barrier();
        __iso_volatile_store32(_Atomic_address_as<int>(_Storage), _Atomic_reinterpret_as<int>(_Value));
        _Memory_barrier();
#else // ^^^ ARM32/ARM64/ARM64EC hardware / x86/x64 hardware vvv
        (void) _InterlockedExchange(_Atomic_address_as<long>(_Storage), _Atomic_reinterpret_as<long>(_Value));
#endif // hardware
    }

    void store(const _TVal _Value, const memory_order _Order) noexcept { // store with given memory order
        const auto _Mem     = _Atomic_address_as<int>(_Storage);
        const int _As_bytes = _Atomic_reinterpret_as<int>(_Value);
        switch (_Order) {
        case memory_order_relaxed:
            __iso_volatile_store32(_Mem, _As_bytes);
            return;
        case memory_order_release:
            _Compiler_or_memory_barrier();
            __iso_volatile_store32(_Mem, _As_bytes);
            return;
        default:
        case memory_order_consume:
        case memory_order_acquire:
        case memory_order_acq_rel:
            _INVALID_MEMORY_ORDER;
            // [[fallthrough]];
        case memory_order_seq_cst:
            store(_Value);
            return;
        }
    }

    _NODISCARD _TVal load() const noexcept { // load with sequential consistency
        const auto _Mem = _Atomic_address_as<int>(_Storage);
        auto _As_bytes  = __iso_volatile_load32(_Mem);
        _Compiler_or_memory_barrier();
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    _NODISCARD _TVal load(const memory_order _Order) const noexcept { // load with given memory order
        const auto _Mem = _Atomic_address_as<int>(_Storage);
        auto _As_bytes  = __iso_volatile_load32(_Mem);
        _Load_barrier(_Order);
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    _TVal exchange(const _TVal _Value, const memory_order _Order = memory_order_seq_cst) noexcept {
        // exchange with given memory order
        long _As_bytes;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _As_bytes, _InterlockedExchange, _Atomic_address_as<long>(_Storage),
            _Atomic_reinterpret_as<long>(_Value));
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    bool compare_exchange_strong(_TVal& _Expected, const _TVal _Desired,
        const memory_order _Order = memory_order_seq_cst) noexcept { // CAS with given memory order
        long _Expected_bytes = _Atomic_reinterpret_as<long>(_Expected); // read before atomic operation
        long _Prev_bytes;
#if _CMPXCHG_MASK_OUT_PADDING_BITS
        if constexpr (_Might_have_non_value_bits<_TVal>) {
            _Storage_for<_TVal> _Mask{_Form_mask};
            const long _Mask_val = _Atomic_reinterpret_as<long>(_Mask);

            for (;;) {
                _ATOMIC_CHOOSE_INTRINSIC(_Order, _Prev_bytes, _InterlockedCompareExchange,
                    _Atomic_address_as<long>(_Storage), _Atomic_reinterpret_as<long>(_Desired), _Expected_bytes);
                if (_Prev_bytes == _Expected_bytes) {
                    return true;
                }

                if ((_Prev_bytes ^ _Expected_bytes) & _Mask_val) {
                    _CSTD memcpy(_STD addressof(_Expected), &_Prev_bytes, sizeof(_TVal));
                    return false;
                }
                _Expected_bytes = (_Expected_bytes & _Mask_val) | (_Prev_bytes & ~_Mask_val);
            }
        }
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Prev_bytes, _InterlockedCompareExchange, _Atomic_address_as<long>(_Storage),
            _Atomic_reinterpret_as<long>(_Desired), _Expected_bytes);
        if (_Prev_bytes == _Expected_bytes) {
            return true;
        }

        _CSTD memcpy(_STD addressof(_Expected), &_Prev_bytes, sizeof(_TVal));
        return false;
    }

#if _HAS_CXX20
    void wait(const _TVal _Expected, const memory_order _Order = memory_order_seq_cst) const noexcept {
        _Atomic_wait_direct(this, _Atomic_reinterpret_as<long>(_Expected), _Order);
    }

    void notify_one() noexcept {
        __std_atomic_notify_one_direct(_STD addressof(_Storage));
    }

    void notify_all() noexcept {
        __std_atomic_notify_all_direct(_STD addressof(_Storage));
    }
#endif // _HAS_CXX20

    typename _Atomic_storage_types<_Ty>::_TStorage _Storage;
};

template <class _Ty>
struct _Atomic_storage<_Ty, 8> { // lock-free using 8-byte intrinsics

    using _TVal = remove_reference_t<_Ty>;

    _Atomic_storage() = default;

    /* implicit */ constexpr _Atomic_storage(conditional_t<is_reference_v<_Ty>, _Ty, const _TVal> _Value) noexcept
        : _Storage{_Value} {
        // non-atomically initialize this atomic
    }

    void store(const _TVal _Value) noexcept { // store with sequential consistency
        const auto _Mem           = _Atomic_address_as<long long>(_Storage);
        const long long _As_bytes = _Atomic_reinterpret_as<long long>(_Value);
#if defined(_M_IX86)
        _Compiler_barrier();
        __iso_volatile_store64(_Mem, _As_bytes);
        _STD atomic_thread_fence(memory_order_seq_cst);
#elif defined(_M_ARM64) || defined(_M_ARM64EC)
        _Memory_barrier();
        __iso_volatile_store64(_Mem, _As_bytes);
        _Memory_barrier();
#else // ^^^ _M_ARM64, _M_ARM64EC / ARM32, x64 vvv
        (void) _InterlockedExchange64(_Mem, _As_bytes);
#endif // ^^^ ARM32, x64 ^^^
    }

    void store(const _TVal _Value, const memory_order _Order) noexcept { // store with given memory order
        const auto _Mem           = _Atomic_address_as<long long>(_Storage);
        const long long _As_bytes = _Atomic_reinterpret_as<long long>(_Value);
        switch (_Order) {
        case memory_order_relaxed:
            __iso_volatile_store64(_Mem, _As_bytes);
            return;
        case memory_order_release:
            _Compiler_or_memory_barrier();
            __iso_volatile_store64(_Mem, _As_bytes);
            return;
        default:
        case memory_order_consume:
        case memory_order_acquire:
        case memory_order_acq_rel:
            _INVALID_MEMORY_ORDER;
            // [[fallthrough]];
        case memory_order_seq_cst:
            store(_Value);
            return;
        }
    }

    _NODISCARD _TVal load() const noexcept { // load with sequential consistency
        const auto _Mem = _Atomic_address_as<long long>(_Storage);
        long long _As_bytes;
#ifdef _M_ARM
        _As_bytes = __ldrexd(_Mem);
        _Memory_barrier();
#else
        _As_bytes = __iso_volatile_load64(_Mem);
        _Compiler_or_memory_barrier();
#endif
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

    _NODISCARD _TVal load(const memory_order _Order) const noexcept { // load with given memory order
        const auto _Mem = _Atomic_address_as<long long>(_Storage);
#ifdef _M_ARM
        long long _As_bytes = __ldrexd(_Mem);
#else
        long long _As_bytes = __iso_volatile_load64(_Mem);
#endif
        _Load_barrier(_Order);
        return reinterpret_cast<_TVal&>(_As_bytes);
    }

#ifdef _M_IX86
    _TVal exchange(const _TVal _Value, const memory_order _Order = memory_order_seq_cst) noexcept {
        // exchange with (effectively) sequential consistency
        _TVal _Temp{load()};
        while (!compare_exchange_strong(_Temp, _Value, _Order)) { // keep trying
        }

        return _Temp;
    }
#else // ^^^ _M_IX86 / !_M_IX86 vvv
    _TVal exchange(const _TVal _Value, const memory_order _Order = memory_order_seq_cst) noexcept {
        // exchange with given memory order
        long long _As_bytes;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _As_bytes, _InterlockedExchange64, _Atomic_address_as<long long>(_Storage),
            _Atomic_reinterpret_as<long long>(_Value));
        return reinterpret_cast<_TVal&>(_As_bytes);
    }
#endif // _M_IX86

    bool compare_exchange_strong(_TVal& _Expected, const _TVal _Desired,
        const memory_order _Order = memory_order_seq_cst) noexcept { // CAS with given memory order
        long long _Expected_bytes = _Atomic_reinterpret_as<long long>(_Expected); // read before atomic operation
        long long _Prev_bytes;

#if _CMPXCHG_MASK_OUT_PADDING_BITS
        if constexpr (_Might_have_non_value_bits<_TVal>) {
            _Storage_for<_TVal> _Mask{_Form_mask};
            const long long _Mask_val = _Atomic_reinterpret_as<long long>(_Mask);

            for (;;) {
                _ATOMIC_CHOOSE_INTRINSIC(_Order, _Prev_bytes, _InterlockedCompareExchange64,
                    _Atomic_address_as<long long>(_Storage), _Atomic_reinterpret_as<long long>(_Desired),
                    _Expected_bytes);
                if (_Prev_bytes == _Expected_bytes) {
                    return true;
                }

                if ((_Prev_bytes ^ _Expected_bytes) & _Mask_val) {
                    _CSTD memcpy(_STD addressof(_Expected), &_Prev_bytes, sizeof(_TVal));
                    return false;
                }
                _Expected_bytes = (_Expected_bytes & _Mask_val) | (_Prev_bytes & ~_Mask_val);
            }
        }
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Prev_bytes, _InterlockedCompareExchange64,
            _Atomic_address_as<long long>(_Storage), _Atomic_reinterpret_as<long long>(_Desired), _Expected_bytes);
        if (_Prev_bytes == _Expected_bytes) {
            return true;
        }

        _CSTD memcpy(_STD addressof(_Expected), &_Prev_bytes, sizeof(_TVal));
        return false;
    }

#if _HAS_CXX20
    void wait(const _TVal _Expected, const memory_order _Order = memory_order_seq_cst) const noexcept {
        _Atomic_wait_direct(this, _Atomic_reinterpret_as<long long>(_Expected), _Order);
    }

    void notify_one() noexcept {
        __std_atomic_notify_one_direct(_STD addressof(_Storage));
    }

    void notify_all() noexcept {
        __std_atomic_notify_all_direct(_STD addressof(_Storage));
    }
#endif // _HAS_CXX20

    typename _Atomic_storage_types<_Ty>::_TStorage _Storage;
};

#ifdef _WIN64
template <class _Ty>
struct _Atomic_storage<_Ty, 16> { // lock-free using 16-byte intrinsics
    // TRANSITION, ABI: replace '_Ty&' with '_Ty' in this specialization
    using _TVal = remove_reference_t<_Ty>;

    _Atomic_storage() = default;

    /* implicit */ constexpr _Atomic_storage(conditional_t<is_reference_v<_Ty>, _Ty, const _TVal> _Value) noexcept
        : _Storage{_Value} {} // non-atomically initialize this atomic

    void store(const _TVal _Value) noexcept { // store with sequential consistency
        (void) exchange(_Value);
    }

    void store(const _TVal _Value, const memory_order _Order) noexcept { // store with given memory order
        _Check_store_memory_order(_Order);
        (void) exchange(_Value, _Order);
    }

    _NODISCARD _TVal load() const noexcept { // load with sequential consistency
        long long* const _Storage_ptr = const_cast<long long*>(_Atomic_address_as<const long long>(_Storage));
        _Int128 _Result{}; // atomic CAS 0 with 0
        (void) _STD_COMPARE_EXCHANGE_128(_Storage_ptr, 0, 0, &_Result._Low);
        return reinterpret_cast<_TVal&>(_Result);
    }

    _NODISCARD _TVal load(const memory_order _Order) const noexcept { // load with given memory order
#if defined(_M_ARM64) || defined(_M_ARM64EC)
        long long* const _Storage_ptr = const_cast<long long*>(_Atomic_address_as<const long long>(_Storage));
        _Int128 _Result{}; // atomic CAS 0 with 0
        switch (_Order) {
        case memory_order_relaxed:
            (void) _INTRIN_RELAXED(_InterlockedCompareExchange128)(_Storage_ptr, 0, 0, &_Result._Low);
            break;
        case memory_order_consume:
        case memory_order_acquire:
            (void) _INTRIN_ACQUIRE(_InterlockedCompareExchange128)(_Storage_ptr, 0, 0, &_Result._Low);
            break;
        default:
        case memory_order_release:
        case memory_order_acq_rel:
            _INVALID_MEMORY_ORDER;
            // [[fallthrough]];
        case memory_order_seq_cst:
            (void) _InterlockedCompareExchange128(_Storage_ptr, 0, 0, &_Result._Low);
            break;
        }

        return reinterpret_cast<_TVal&>(_Result);
#else // ^^^ _M_ARM64, _M_ARM64EC / _M_X64 vvv
        _Check_load_memory_order(_Order);
        return load();
#endif // ^^^ _M_X64 ^^^
    }

    _TVal exchange(const _TVal _Value) noexcept { // exchange with sequential consistency
        _TVal _Result{_Value};
        while (!compare_exchange_strong(_Result, _Value)) { // keep trying
        }

        return _Result;
    }

    _TVal exchange(const _TVal _Value, const memory_order _Order) noexcept { // exchange with given memory order
        _TVal _Result{_Value};
        while (!compare_exchange_strong(_Result, _Value, _Order)) { // keep trying
        }

        return _Result;
    }

    bool compare_exchange_strong(_TVal& _Expected, const _TVal _Desired,
        const memory_order _Order = memory_order_seq_cst) noexcept { // CAS with given memory order
        _Int128 _Desired_bytes{};
        _CSTD memcpy(&_Desired_bytes, _STD addressof(_Desired), sizeof(_TVal));
        _Int128 _Expected_temp{};
        _CSTD memcpy(&_Expected_temp, _STD addressof(_Expected), sizeof(_TVal));
        unsigned char _Result;
#if _CMPXCHG_MASK_OUT_PADDING_BITS
        if constexpr (_Might_have_non_value_bits<_TVal>) {
            _Int128 _Expected_originally{};
            _CSTD memcpy(&_Expected_originally, _STD addressof(_Expected), sizeof(_TVal));

            _Storage_for<_TVal> _Mask{_Form_mask};
            _Int128 _Mask_val{};
            _CSTD memcpy(&_Mask_val, _Mask._Ptr(), sizeof(_TVal));
            for (;;) {
#if defined(_M_ARM64) || defined(_M_ARM64EC)
                _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedCompareExchange128,
                    _Atomic_address_as<long long>(_Storage), _Desired_bytes._High, _Desired_bytes._Low,
                    &_Expected_temp._Low);
#else // ^^^ _M_ARM64, _M_ARM64EC / _M_X64 vvv
                (void) _Order;
                _Result = _STD_COMPARE_EXCHANGE_128(&reinterpret_cast<long long&>(_Storage), _Desired_bytes._High,
                    _Desired_bytes._Low, &_Expected_temp._Low);
#endif // ^^^ _M_X64 ^^^
                if (_Result) {
                    return true;
                }

                if (((_Expected_temp._Low ^ _Expected_originally._Low) & _Mask_val._Low) != 0
                    || ((_Expected_temp._High ^ _Expected_originally._High) & _Mask_val._High) != 0) {
                    _CSTD memcpy(_STD addressof(_Expected), &_Expected_temp, sizeof(_TVal));
                    return false;
                }

                _Expected_temp._Low =
                    (_Expected_originally._Low & _Mask_val._Low) | (_Expected_temp._Low & ~_Mask_val._Low);
                _Expected_temp._High =
                    (_Expected_originally._High & _Mask_val._High) | (_Expected_temp._High & ~_Mask_val._High);
            }
        }
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS
#if defined(_M_ARM64) || defined(_M_ARM64EC)
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedCompareExchange128,
            _Atomic_address_as<long long>(_Storage), _Desired_bytes._High, _Desired_bytes._Low, &_Expected_temp._Low);
#else // ^^^ _M_ARM64, _M_ARM64EC / _M_X64 vvv
        (void) _Order;
        _Result = _STD_COMPARE_EXCHANGE_128(
            &reinterpret_cast<long long&>(_Storage), _Desired_bytes._High, _Desired_bytes._Low, &_Expected_temp._Low);
#endif // ^^^ _M_X64 ^^^
        if (_Result == 0) {
            _CSTD memcpy(_STD addressof(_Expected), &_Expected_temp, sizeof(_TVal));
        }

        return _Result != 0;
    }

#if _HAS_CXX20
    void wait(_TVal _Expected, memory_order _Order = memory_order_seq_cst) const noexcept {
        const auto _Storage_ptr  = _STD addressof(_Storage);
        const auto _Expected_ptr = _STD addressof(_Expected);
        _Int128 _Expected_bytes  = reinterpret_cast<const _Int128&>(_Expected);

        for (;;) {
            const _TVal _Observed   = load(_Order);
            _Int128 _Observed_bytes = reinterpret_cast<const _Int128&>(_Observed);
            if (_Observed_bytes._Low != _Expected_bytes._Low || _Observed_bytes._High != _Expected_bytes._High) {
#if _CMPXCHG_MASK_OUT_PADDING_BITS
                if constexpr (_Might_have_non_value_bits<_TVal>) {
                    _Storage_for<_TVal> _Mask{_Form_mask};
                    const _Int128 _Mask_val = reinterpret_cast<const _Int128&>(_Mask._Ref());

                    if (((_Expected_bytes._Low ^ _Observed_bytes._Low) & _Mask_val._Low) == 0
                        && ((_Expected_bytes._High ^ _Observed_bytes._High) & _Mask_val._High) == 0) {
                        _Expected_bytes = _Observed_bytes;
                        continue;
                    }
                }
#endif // _CMPXCHG_MASK_OUT_PADDING_BITS

                return;
            }

            __std_atomic_wait_indirect(_Storage_ptr, _Expected_ptr, sizeof(_TVal), nullptr,
                &_Atomic_wait_compare_16_bytes, _Atomic_wait_no_timeout);
        }
    }

    void notify_one() noexcept {
        __std_atomic_notify_one_indirect(_STD addressof(_Storage));
    }

    void notify_all() noexcept {
        __std_atomic_notify_all_indirect(_STD addressof(_Storage));
    }
#endif // _HAS_CXX20

    struct _Int128 {
        alignas(16) long long _Low;
        long long _High;
    };

    typename _Atomic_storage_types<_Ty>::_TStorage _Storage;
};
#endif // _WIN64

template <class _Ty, size_t = sizeof(_Ty)>
struct _Atomic_integral; // not defined

template <class _Ty>
struct _Atomic_integral<_Ty, 1> : _Atomic_storage<_Ty> { // atomic integral operations using 1-byte intrinsics
    using _Base = _Atomic_storage<_Ty>;
    using typename _Base::_TVal;

    using _Base::_Base;

    _TVal fetch_add(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        char _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedExchangeAdd8, _Atomic_address_as<char>(this->_Storage),
            static_cast<char>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_and(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        char _Result;
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedAnd8, _Atomic_address_as<char>(this->_Storage), static_cast<char>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_or(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        char _Result;
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedOr8, _Atomic_address_as<char>(this->_Storage), static_cast<char>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_xor(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        char _Result;
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedXor8, _Atomic_address_as<char>(this->_Storage), static_cast<char>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal operator++(int) noexcept {
        return static_cast<_TVal>(_InterlockedExchangeAdd8(_Atomic_address_as<char>(this->_Storage), 1));
    }

    _TVal operator++() noexcept {
        unsigned char _Before =
            static_cast<unsigned char>(_InterlockedExchangeAdd8(_Atomic_address_as<char>(this->_Storage), 1));
        ++_Before;
        return static_cast<_TVal>(_Before);
    }

    _TVal operator--(int) noexcept {
        return static_cast<_TVal>(_InterlockedExchangeAdd8(_Atomic_address_as<char>(this->_Storage), -1));
    }

    _TVal operator--() noexcept {
        unsigned char _Before =
            static_cast<unsigned char>(_InterlockedExchangeAdd8(_Atomic_address_as<char>(this->_Storage), -1));
        --_Before;
        return static_cast<_TVal>(_Before);
    }
};

template <class _Ty>
struct _Atomic_integral<_Ty, 2> : _Atomic_storage<_Ty> { // atomic integral operations using 2-byte intrinsics
    using _Base = _Atomic_storage<_Ty>;
    using typename _Base::_TVal;

    using _Base::_Base;

    _TVal fetch_add(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        short _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedExchangeAdd16, _Atomic_address_as<short>(this->_Storage),
            static_cast<short>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_and(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        short _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedAnd16, _Atomic_address_as<short>(this->_Storage),
            static_cast<short>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_or(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        short _Result;
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedOr16, _Atomic_address_as<short>(this->_Storage), static_cast<short>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_xor(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        short _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedXor16, _Atomic_address_as<short>(this->_Storage),
            static_cast<short>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal operator++(int) noexcept {
        unsigned short _After =
            static_cast<unsigned short>(_InterlockedIncrement16(_Atomic_address_as<short>(this->_Storage)));
        --_After;
        return static_cast<_TVal>(_After);
    }

    _TVal operator++() noexcept {
        return static_cast<_TVal>(_InterlockedIncrement16(_Atomic_address_as<short>(this->_Storage)));
    }

    _TVal operator--(int) noexcept {
        unsigned short _After =
            static_cast<unsigned short>(_InterlockedDecrement16(_Atomic_address_as<short>(this->_Storage)));
        ++_After;
        return static_cast<_TVal>(_After);
    }

    _TVal operator--() noexcept {
        return static_cast<_TVal>(_InterlockedDecrement16(_Atomic_address_as<short>(this->_Storage)));
    }
};

template <class _Ty>
struct _Atomic_integral<_Ty, 4> : _Atomic_storage<_Ty> { // atomic integral operations using 4-byte intrinsics
    using _Base = _Atomic_storage<_Ty>;
    using typename _Base::_TVal;

    using _Base::_Base;

    _TVal fetch_add(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        long _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedExchangeAdd, _Atomic_address_as<long>(this->_Storage),
            static_cast<long>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_and(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        long _Result;
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedAnd, _Atomic_address_as<long>(this->_Storage), static_cast<long>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_or(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        long _Result;
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedOr, _Atomic_address_as<long>(this->_Storage), static_cast<long>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_xor(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        long _Result;
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedXor, _Atomic_address_as<long>(this->_Storage), static_cast<long>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal operator++(int) noexcept {
        unsigned long _After =
            static_cast<unsigned long>(_InterlockedIncrement(_Atomic_address_as<long>(this->_Storage)));
        --_After;
        return static_cast<_TVal>(_After);
    }

    _TVal operator++() noexcept {
        return static_cast<_TVal>(_InterlockedIncrement(_Atomic_address_as<long>(this->_Storage)));
    }

    _TVal operator--(int) noexcept {
        unsigned long _After =
            static_cast<unsigned long>(_InterlockedDecrement(_Atomic_address_as<long>(this->_Storage)));
        ++_After;
        return static_cast<_TVal>(_After);
    }

    _TVal operator--() noexcept {
        return static_cast<_TVal>(_InterlockedDecrement(_Atomic_address_as<long>(this->_Storage)));
    }
};

template <class _Ty>
struct _Atomic_integral<_Ty, 8> : _Atomic_storage<_Ty> { // atomic integral operations using 8-byte intrinsics
    using _Base = _Atomic_storage<_Ty>;
    using typename _Base::_TVal;

    using _Base::_Base;

#ifdef _M_IX86
    _TVal fetch_add(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        // effectively sequential consistency
        _TVal _Temp{this->load()};
        while (!this->compare_exchange_strong(_Temp, _Temp + _Operand, _Order)) { // keep trying
        }

        return _Temp;
    }

    _TVal fetch_and(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        // effectively sequential consistency
        _TVal _Temp{this->load()};
        while (!this->compare_exchange_strong(_Temp, _Temp & _Operand, _Order)) { // keep trying
        }

        return _Temp;
    }

    _TVal fetch_or(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        // effectively sequential consistency
        _TVal _Temp{this->load()};
        while (!this->compare_exchange_strong(_Temp, _Temp | _Operand, _Order)) { // keep trying
        }

        return _Temp;
    }

    _TVal fetch_xor(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        // effectively sequential consistency
        _TVal _Temp{this->load()};
        while (!this->compare_exchange_strong(_Temp, _Temp ^ _Operand, _Order)) { // keep trying
        }

        return _Temp;
    }

    _TVal operator++(int) noexcept {
        return fetch_add(static_cast<_TVal>(1));
    }

    _TVal operator++() noexcept {
        return fetch_add(static_cast<_TVal>(1)) + static_cast<_TVal>(1);
    }

    _TVal operator--(int) noexcept {
        return fetch_add(static_cast<_TVal>(-1));
    }

    _TVal operator--() noexcept {
        return fetch_add(static_cast<_TVal>(-1)) - static_cast<_TVal>(1);
    }

#else // ^^^ _M_IX86 / !_M_IX86 vvv
    _TVal fetch_add(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        long long _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedExchangeAdd64,
            _Atomic_address_as<long long>(this->_Storage), static_cast<long long>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_and(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        long long _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedAnd64, _Atomic_address_as<long long>(this->_Storage),
            static_cast<long long>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_or(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        long long _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedOr64, _Atomic_address_as<long long>(this->_Storage),
            static_cast<long long>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal fetch_xor(const _TVal _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        long long _Result;
        _ATOMIC_CHOOSE_INTRINSIC(_Order, _Result, _InterlockedXor64, _Atomic_address_as<long long>(this->_Storage),
            static_cast<long long>(_Operand));
        return static_cast<_TVal>(_Result);
    }

    _TVal operator++(int) noexcept {
        unsigned long long _After =
            static_cast<unsigned long long>(_InterlockedIncrement64(_Atomic_address_as<long long>(this->_Storage)));
        --_After;
        return static_cast<_TVal>(_After);
    }

    _TVal operator++() noexcept {
        return static_cast<_TVal>(_InterlockedIncrement64(_Atomic_address_as<long long>(this->_Storage)));
    }

    _TVal operator--(int) noexcept {
        unsigned long long _After =
            static_cast<unsigned long long>(_InterlockedDecrement64(_Atomic_address_as<long long>(this->_Storage)));
        ++_After;
        return static_cast<_TVal>(_After);
    }

    _TVal operator--() noexcept {
        return static_cast<_TVal>(_InterlockedDecrement64(_Atomic_address_as<long long>(this->_Storage)));
    }
#endif // _M_IX86
};

#if 1 // TRANSITION, ABI
template <size_t _TypeSize>
_INLINE_VAR constexpr bool _Is_always_lock_free = _TypeSize <= 8 && (_TypeSize & (_TypeSize - 1)) == 0;
#else // ^^^ don't break ABI / break ABI vvv
#if _ATOMIC_HAS_DCAS
template <size_t _TypeSize>
_INLINE_VAR constexpr bool _Is_always_lock_free = _TypeSize <= 2 * sizeof(void*);
#else // ^^^ _ATOMIC_HAS_DCAS / !_ATOMIC_HAS_DCAS vvv
template <size_t _TypeSize>
_INLINE_VAR constexpr bool _Is_always_lock_free = _TypeSize <= sizeof(void*);
#endif // _ATOMIC_HAS_DCAS
#endif // break ABI

template <class _Ty, bool _Is_lock_free = _Is_always_lock_free<sizeof(_Ty)>>
_INLINE_VAR constexpr bool _Deprecate_non_lock_free_volatile = true;

template <class _Ty>
_CXX20_DEPRECATE_VOLATILE _INLINE_VAR constexpr bool _Deprecate_non_lock_free_volatile<_Ty, false> = true;

template <class _Ty>
struct _Atomic_integral_facade : _Atomic_integral<_Ty> {
    // provides operator overloads and other support for atomic integral specializations
    using _Base           = _Atomic_integral<_Ty>;
    using difference_type = _Ty;

    using _Base::_Base;

    // _Deprecate_non_lock_free_volatile is unnecessary here.

    // note: const_cast-ing away volatile is safe because all our intrinsics add volatile back on.
    // We make the primary functions non-volatile for better debug codegen, as non-volatile atomics
    // are far more common than volatile ones.
    using _Base::fetch_add;
    _Ty fetch_add(const _Ty _Operand) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_add(_Operand);
    }

    _Ty fetch_add(const _Ty _Operand, const memory_order _Order) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_add(_Operand, _Order);
    }

    _NODISCARD static _Ty _Negate(const _Ty _Value) noexcept { // returns two's complement negated value of _Value
        return static_cast<_Ty>(0U - static_cast<make_unsigned_t<_Ty>>(_Value));
    }

    _Ty fetch_sub(const _Ty _Operand) noexcept {
        return fetch_add(_Negate(_Operand));
    }

    _Ty fetch_sub(const _Ty _Operand) volatile noexcept {
        return fetch_add(_Negate(_Operand));
    }

    _Ty fetch_sub(const _Ty _Operand, const memory_order _Order) noexcept {
        return fetch_add(_Negate(_Operand), _Order);
    }

    _Ty fetch_sub(const _Ty _Operand, const memory_order _Order) volatile noexcept {
        return fetch_add(_Negate(_Operand), _Order);
    }

    using _Base::fetch_and;
    _Ty fetch_and(const _Ty _Operand) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_and(_Operand);
    }

    _Ty fetch_and(const _Ty _Operand, const memory_order _Order) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_and(_Operand, _Order);
    }

    using _Base::fetch_or;
    _Ty fetch_or(const _Ty _Operand) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_or(_Operand);
    }

    _Ty fetch_or(const _Ty _Operand, const memory_order _Order) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_or(_Operand, _Order);
    }

    using _Base::fetch_xor;
    _Ty fetch_xor(const _Ty _Operand) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_xor(_Operand);
    }

    _Ty fetch_xor(const _Ty _Operand, const memory_order _Order) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_xor(_Operand, _Order);
    }

    using _Base::operator++;
    _Ty operator++(int) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::operator++(0);
    }

    _Ty operator++() volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::operator++();
    }

    using _Base::operator--;
    _Ty operator--(int) volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::operator--(0);
    }

    _Ty operator--() volatile noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::operator--();
    }

    _Ty operator+=(const _Ty _Operand) noexcept {
        return static_cast<_Ty>(this->_Base::fetch_add(_Operand) + _Operand);
    }

    _Ty operator+=(const _Ty _Operand) volatile noexcept {
        return static_cast<_Ty>(const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_add(_Operand) + _Operand);
    }

    _Ty operator-=(const _Ty _Operand) noexcept {
        return static_cast<_Ty>(fetch_sub(_Operand) - _Operand);
    }

    _Ty operator-=(const _Ty _Operand) volatile noexcept {
        return static_cast<_Ty>(const_cast<_Atomic_integral_facade*>(this)->fetch_sub(_Operand) - _Operand);
    }

    _Ty operator&=(const _Ty _Operand) noexcept {
        return static_cast<_Ty>(this->_Base::fetch_and(_Operand) & _Operand);
    }

    _Ty operator&=(const _Ty _Operand) volatile noexcept {
        return static_cast<_Ty>(const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_and(_Operand) & _Operand);
    }

    _Ty operator|=(const _Ty _Operand) noexcept {
        return static_cast<_Ty>(this->_Base::fetch_or(_Operand) | _Operand);
    }

    _Ty operator|=(const _Ty _Operand) volatile noexcept {
        return static_cast<_Ty>(const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_or(_Operand) | _Operand);
    }

    _Ty operator^=(const _Ty _Operand) noexcept {
        return static_cast<_Ty>(this->_Base::fetch_xor(_Operand) ^ _Operand);
    }

    _Ty operator^=(const _Ty _Operand) volatile noexcept {
        return static_cast<_Ty>(const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_xor(_Operand) ^ _Operand);
    }
};

template <class _Ty>
struct _Atomic_integral_facade<_Ty&> : _Atomic_integral<_Ty&> {
    // provides operator overloads and other support for atomic integral specializations
    using _Base           = _Atomic_integral<_Ty&>;
    using difference_type = _Ty;

    using _Base::_Base;

    _NODISCARD static _Ty _Negate(const _Ty _Value) noexcept { // returns two's complement negated value of _Value
        return static_cast<_Ty>(0U - static_cast<make_unsigned_t<_Ty>>(_Value));
    }

    _Ty fetch_add(const _Ty _Operand) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_add(_Operand);
    }

    _Ty fetch_add(const _Ty _Operand, const memory_order _Order) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_add(_Operand, _Order);
    }

    _Ty fetch_sub(const _Ty _Operand) const noexcept {
        return fetch_add(_Negate(_Operand));
    }

    _Ty fetch_sub(const _Ty _Operand, const memory_order _Order) const noexcept {
        return fetch_add(_Negate(_Operand), _Order);
    }

    _Ty operator++(int) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::operator++(0);
    }

    _Ty operator++() const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::operator++();
    }

    _Ty operator--(int) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::operator--(0);
    }

    _Ty operator--() const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::operator--();
    }

    _Ty operator+=(const _Ty _Operand) const noexcept {
        return static_cast<_Ty>(fetch_add(_Operand) + _Operand);
    }

    _Ty operator-=(const _Ty _Operand) const noexcept {
        return static_cast<_Ty>(fetch_sub(_Operand) - _Operand);
    }

    _Ty fetch_and(const _Ty _Operand) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_and(_Operand);
    }

    _Ty fetch_and(const _Ty _Operand, const memory_order _Order) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_and(_Operand, _Order);
    }

    _Ty fetch_or(const _Ty _Operand) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_or(_Operand);
    }

    _Ty fetch_or(const _Ty _Operand, const memory_order _Order) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_or(_Operand, _Order);
    }

    _Ty fetch_xor(const _Ty _Operand) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_xor(_Operand);
    }

    _Ty fetch_xor(const _Ty _Operand, const memory_order _Order) const noexcept {
        return const_cast<_Atomic_integral_facade*>(this)->_Base::fetch_xor(_Operand, _Order);
    }

    _Ty operator&=(const _Ty _Operand) const noexcept {
        return static_cast<_Ty>(fetch_and(_Operand) & _Operand);
    }

    _Ty operator|=(const _Ty _Operand) const noexcept {
        return static_cast<_Ty>(fetch_or(_Operand) | _Operand);
    }

    _Ty operator^=(const _Ty _Operand) const noexcept {
        return static_cast<_Ty>(fetch_xor(_Operand) ^ _Operand);
    }
};

#if _HAS_CXX20
template <class _Ty>
struct _Atomic_floating : _Atomic_storage<_Ty> {
    // provides atomic floating-point operations
    using _Base           = _Atomic_storage<_Ty>;
    using difference_type = _Ty;

    using _Base::_Base;

    _Ty fetch_add(const _Ty _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        _Ty _Temp{this->load(memory_order_relaxed)};
        while (!this->compare_exchange_strong(_Temp, _Temp + _Operand, _Order)) { // keep trying
        }

        return _Temp;
    }

    // _Deprecate_non_lock_free_volatile is unnecessary here.

    // note: const_cast-ing away volatile is safe because all our intrinsics add volatile back on.
    // We make the primary functions non-volatile for better debug codegen, as non-volatile atomics
    // are far more common than volatile ones.
    _Ty fetch_add(const _Ty _Operand, const memory_order _Order = memory_order_seq_cst) volatile noexcept {
        return const_cast<_Atomic_floating*>(this)->fetch_add(_Operand, _Order);
    }

    _Ty fetch_sub(const _Ty _Operand, const memory_order _Order = memory_order_seq_cst) noexcept {
        _Ty _Temp{this->load(memory_order_relaxed)};
        while (!this->compare_exchange_strong(_Temp, _Temp - _Operand, _Order)) { // keep trying
        }

        return _Temp;
    }

    _Ty fetch_sub(const _Ty _Operand, const memory_order _Order = memory_order_seq_cst) volatile noexcept {
        return const_cast<_Atomic_floating*>(this)->fetch_sub(_Operand, _Order);
    }

    _Ty operator+=(const _Ty _Operand) noexcept {
        return fetch_add(_Operand) + _Operand;
    }

    _Ty operator+=(const _Ty _Operand) volatile noexcept {
        return const_cast<_Atomic_floating*>(this)->fetch_add(_Operand) + _Operand;
    }

    _Ty operator-=(const _Ty _Operand) noexcept {
        return fetch_sub(_Operand) - _Operand;
    }

    _Ty operator-=(const _Ty _Operand) volatile noexcept {
        return const_cast<_Atomic_floating*>(this)->fetch_sub(_Operand) - _Operand;
    }
};

template <class _Ty>
struct _Atomic_floating<_Ty&> : _Atomic_storage<_Ty&> {
    // provides atomic floating-point operations
    using _Base           = _Atomic_storage<_Ty&>;
    using difference_type = _Ty;

    using _Base::_Base;

    _Ty fetch_add(const _Ty _Operand, const memory_order _Order = memory_order_seq_cst) const noexcept {
        _Ty _Temp{this->load(memory_order_relaxed)};
        while (!const_cast<_Atomic_floating*>(this)->_Base::compare_exchange_strong(
            _Temp, _Temp + _Operand, _Order)) { // keep trying
        }

        return _Temp;
    }

    _Ty fetch_sub(const _Ty _Operand, const memory_order _Order = memory_order_seq_cst) const noexcept {
        _Ty _Temp{this->load(memory_order_relaxed)};
        while (!const_cast<_Atomic_floating*>(this)->_Base::compare_exchange_strong(
            _Temp, _Temp - _Operand, _Order)) { // keep trying
        }

        return _Temp;
    }

    _Ty operator+=(const _Ty _Operand) const noexcept {
        return fetch_add(_Operand) + _Operand;
    }

    _Ty operator-=(const _Ty _Operand) const noexcept {
        return fetch_sub(_Operand) - _Operand;
    }
};
#endif // _HAS_CXX20

template <class _Ty>
struct _Atomic_pointer : _Atomic_storage<_Ty> {
    using _Base           = _Atomic_storage<_Ty>;
    using difference_type = ptrdiff_t;

    using _Base::_Base;

    _Ty fetch_add(const ptrdiff_t _Diff, const memory_order _Order = memory_order_seq_cst) noexcept {
        const ptrdiff_t _Shift_bytes =
            static_cast<ptrdiff_t>(static_cast<size_t>(_Diff) * sizeof(remove_pointer_t<_Ty>));
        ptrdiff_t _Result;
#if defined(_M_IX86) || defined(_M_ARM)
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedExchangeAdd, _Atomic_address_as<long>(this->_Storage), _Shift_bytes);
#else // ^^^ 32 bits / 64 bits vvv
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedExchangeAdd64, _Atomic_address_as<long long>(this->_Storage), _Shift_bytes);
#endif // hardware
        return reinterpret_cast<_Ty>(_Result);
    }

    // _Deprecate_non_lock_free_volatile is unnecessary here.

    _Ty fetch_add(const ptrdiff_t _Diff) volatile noexcept {
        return const_cast<_Atomic_pointer*>(this)->fetch_add(_Diff);
    }

    _Ty fetch_add(const ptrdiff_t _Diff, const memory_order _Order) volatile noexcept {
        return const_cast<_Atomic_pointer*>(this)->fetch_add(_Diff, _Order);
    }

    _Ty fetch_sub(const ptrdiff_t _Diff) volatile noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff)));
    }

    _Ty fetch_sub(const ptrdiff_t _Diff) noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff)));
    }

    _Ty fetch_sub(const ptrdiff_t _Diff, const memory_order _Order) volatile noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff)), _Order);
    }

    _Ty fetch_sub(const ptrdiff_t _Diff, const memory_order _Order) noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff)), _Order);
    }

    _Ty operator++(int) volatile noexcept {
        return fetch_add(1);
    }

    _Ty operator++(int) noexcept {
        return fetch_add(1);
    }

    _Ty operator++() volatile noexcept {
        return fetch_add(1) + 1;
    }

    _Ty operator++() noexcept {
        return fetch_add(1) + 1;
    }

    _Ty operator--(int) volatile noexcept {
        return fetch_add(-1);
    }

    _Ty operator--(int) noexcept {
        return fetch_add(-1);
    }

    _Ty operator--() volatile noexcept {
        return fetch_add(-1) - 1;
    }

    _Ty operator--() noexcept {
        return fetch_add(-1) - 1;
    }

    _Ty operator+=(const ptrdiff_t _Diff) volatile noexcept {
        return fetch_add(_Diff) + _Diff;
    }

    _Ty operator+=(const ptrdiff_t _Diff) noexcept {
        return fetch_add(_Diff) + _Diff;
    }

    _Ty operator-=(const ptrdiff_t _Diff) volatile noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff))) - _Diff;
    }

    _Ty operator-=(const ptrdiff_t _Diff) noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff))) - _Diff;
    }
};


template <class _Ty>
struct _Atomic_pointer<_Ty&> : _Atomic_storage<_Ty&> {
    using _Base           = _Atomic_storage<_Ty&>;
    using difference_type = ptrdiff_t;

    using _Base::_Base;

    _Ty fetch_add(const ptrdiff_t _Diff, const memory_order _Order = memory_order_seq_cst) const noexcept {
        const ptrdiff_t _Shift_bytes =
            static_cast<ptrdiff_t>(static_cast<size_t>(_Diff) * sizeof(remove_pointer_t<_Ty>));
        ptrdiff_t _Result;
#if defined(_M_IX86) || defined(_M_ARM)
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedExchangeAdd, _Atomic_address_as<long>(this->_Storage), _Shift_bytes);
#else // ^^^ 32 bits / 64 bits vvv
        _ATOMIC_CHOOSE_INTRINSIC(
            _Order, _Result, _InterlockedExchangeAdd64, _Atomic_address_as<long long>(this->_Storage), _Shift_bytes);
#endif // hardware
        return reinterpret_cast<_Ty>(_Result);
    }

    _Ty fetch_sub(const ptrdiff_t _Diff) const noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff)));
    }

    _Ty fetch_sub(const ptrdiff_t _Diff, const memory_order _Order) const noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff)), _Order);
    }

    _Ty operator++(int) const noexcept {
        return fetch_add(1);
    }

    _Ty operator++() const noexcept {
        return fetch_add(1) + 1;
    }

    _Ty operator--(int) const noexcept {
        return fetch_add(-1);
    }

    _Ty operator--() const noexcept {
        return fetch_add(-1) - 1;
    }

    _Ty operator+=(const ptrdiff_t _Diff) const noexcept {
        return fetch_add(_Diff) + _Diff;
    }

    _Ty operator-=(const ptrdiff_t _Diff) const noexcept {
        return fetch_add(static_cast<ptrdiff_t>(0 - static_cast<size_t>(_Diff))) - _Diff;
    }
};


#define ATOMIC_VAR_INIT(_Value) \
    { _Value }

template <class _TVal, class _Ty = _TVal>
using _Choose_atomic_base2_t =
    typename _Select<is_integral_v<_TVal> && !is_same_v<bool, _TVal>>::template _Apply<_Atomic_integral_facade<_Ty>,
        typename _Select<is_pointer_v<_TVal> && is_object_v<remove_pointer_t<_TVal>>>::template _Apply<
            _Atomic_pointer<_Ty>, _Atomic_storage<_Ty>>>;

#if _HAS_CXX20
template <class _TVal, class _Ty = _TVal>
using _Choose_atomic_base_t = typename _Select<is_floating_point_v<_TVal>>::template _Apply<_Atomic_floating<_Ty>,
    _Choose_atomic_base2_t<_TVal, _Ty>>;
#else // ^^^ _HAS_CXX20 // !_HAS_CXX20 vvv
template <class _TVal, class _Ty = _TVal>
using _Choose_atomic_base_t = _Choose_atomic_base2_t<_TVal, _Ty>;
#endif // _HAS_CXX20

template <class _Ty>
struct atomic : _Choose_atomic_base_t<_Ty> { // atomic value
private:
    using _Base = _Choose_atomic_base_t<_Ty>;

public:
    static_assert(is_trivially_copyable_v<_Ty> && is_copy_constructible_v<_Ty> && is_move_constructible_v<_Ty> //
                      && is_copy_assignable_v<_Ty> && is_move_assignable_v<_Ty>,
        "atomic<T> requires T to be trivially copyable, copy constructible, move constructible, copy assignable, "
        "and move assignable.");

    using value_type = _Ty;

    using _Base::_Base;

    constexpr atomic() noexcept(is_nothrow_default_constructible_v<_Ty>) : _Base() {}

    atomic(const atomic&) = delete;
    atomic& operator=(const atomic&) = delete;

#if _HAS_CXX17
    static constexpr bool is_always_lock_free = _Is_always_lock_free<sizeof(_Ty)>;
#endif // _HAS_CXX17

#if 1 // TRANSITION, ABI
    _NODISCARD bool is_lock_free() const volatile noexcept {
        constexpr bool _Result = sizeof(_Ty) <= 8 && (sizeof(_Ty) & sizeof(_Ty) - 1) == 0;
        return _Result;
    }

#else // ^^^ don't break ABI / break ABI vvv

    _NODISCARD bool is_lock_free() const volatile noexcept {
#if _ATOMIC_HAS_DCAS
        return sizeof(_Ty) <= 2 * sizeof(void*);
#else // ^^^ _ATOMIC_HAS_DCAS / !_ATOMIC_HAS_DCAS vvv
        return sizeof(_Ty) <= sizeof(void*) || (sizeof(_Ty) <= 2 * sizeof(void*) && __std_atomic_has_cmpxchg16b());
#endif // _ATOMIC_HAS_DCAS
    }
#endif // TRANSITION, ABI

    _NODISCARD bool is_lock_free() const noexcept {
        return static_cast<const volatile atomic*>(this)->is_lock_free();
    }

    _Ty operator=(const _Ty _Value) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        this->store(_Value);
        return _Value;
    }

    _Ty operator=(const _Ty _Value) noexcept {
        this->store(_Value);
        return _Value;
    }

    // For the following, we do the real implementation in the non-volatile function, and const_cast
    // to call the non-volatile function in the volatile one. This is safe because all of the
    // non-volatile functions reapply volatile, as all our intrinsics accept only volatile T *.
    // We expect most atomic<T>s to be non-volatile, so making the real implementations
    // non-volatile should result in better debug codegen.
    using _Base::store;
    void store(const _Ty _Value) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        const_cast<atomic*>(this)->_Base::store(_Value);
    }

    void store(const _Ty _Value, const memory_order _Order) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        const_cast<atomic*>(this)->_Base::store(_Value, _Order);
    }

    using _Base::load;
    _NODISCARD _Ty load() const volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return const_cast<const atomic*>(this)->_Base::load();
    }

    _NODISCARD _Ty load(const memory_order _Order) const volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return const_cast<const atomic*>(this)->_Base::load(_Order);
    }

    using _Base::exchange;
    _Ty exchange(const _Ty _Value) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return const_cast<atomic*>(this)->_Base::exchange(_Value);
    }

    _Ty exchange(const _Ty _Value, const memory_order _Order) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return const_cast<atomic*>(this)->_Base::exchange(_Value, _Order);
    }

    using _Base::compare_exchange_strong;
    bool compare_exchange_strong(_Ty& _Expected, const _Ty _Desired) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return const_cast<atomic*>(this)->_Base::compare_exchange_strong(_Expected, _Desired);
    }

    bool compare_exchange_strong(_Ty& _Expected, const _Ty _Desired, const memory_order _Order) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return const_cast<atomic*>(this)->_Base::compare_exchange_strong(_Expected, _Desired, _Order);
    }

    bool compare_exchange_strong(_Ty& _Expected, const _Ty _Desired, const memory_order _Success,
        const memory_order _Failure) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return this->compare_exchange_strong(_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
    }

    bool compare_exchange_strong(
        _Ty& _Expected, const _Ty _Desired, const memory_order _Success, const memory_order _Failure) noexcept {
        return this->compare_exchange_strong(_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
    }

    bool compare_exchange_weak(_Ty& _Expected, const _Ty _Desired) volatile noexcept {
        // we have no weak CAS intrinsics, even on ARM32/ARM64, so fall back to strong
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return this->compare_exchange_strong(_Expected, _Desired);
    }

    bool compare_exchange_weak(_Ty& _Expected, const _Ty _Desired) noexcept {
        return this->compare_exchange_strong(_Expected, _Desired);
    }

    bool compare_exchange_weak(_Ty& _Expected, const _Ty _Desired, const memory_order _Order) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return this->compare_exchange_strong(_Expected, _Desired, _Order);
    }

    bool compare_exchange_weak(_Ty& _Expected, const _Ty _Desired, const memory_order _Order) noexcept {
        return this->compare_exchange_strong(_Expected, _Desired, _Order);
    }

    bool compare_exchange_weak(_Ty& _Expected, const _Ty _Desired, const memory_order _Success,
        const memory_order _Failure) volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return this->compare_exchange_strong(_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
    }

    bool compare_exchange_weak(
        _Ty& _Expected, const _Ty _Desired, const memory_order _Success, const memory_order _Failure) noexcept {
        return this->compare_exchange_strong(_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
    }

#if _HAS_CXX20
    using _Base::wait;
    void wait(const _Ty _Expected, const memory_order _Order = memory_order_seq_cst) const volatile noexcept {
        const_cast<const atomic*>(this)->_Base::wait(_Expected, _Order);
    }

    using _Base::notify_one;
    void notify_one() volatile noexcept {
        const_cast<atomic*>(this)->_Base::notify_one();
    }

    using _Base::notify_all;
    void notify_all() volatile noexcept {
        const_cast<atomic*>(this)->_Base::notify_all();
    }
#endif // _HAS_CXX20

    operator _Ty() const volatile noexcept {
        static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
        return this->load();
    }

    operator _Ty() const noexcept {
        return this->load();
    }
};

#if _HAS_CXX17
template <class _Ty>
atomic(_Ty) -> atomic<_Ty>;
#endif // _HAS_CXX17

#if _HAS_CXX20
template <class _Ty>
struct atomic_ref : _Choose_atomic_base_t<_Ty, _Ty&> { // atomic reference
private:
    using _Base = _Choose_atomic_base_t<_Ty, _Ty&>;

public:
    static_assert(is_trivially_copyable_v<_Ty>, "atomic_ref<T> requires T to be trivially copyable.");

    using value_type = _Ty;

    explicit atomic_ref(_Ty& _Value) noexcept /* strengthened */ : _Base(_Value) {
        if constexpr (_Is_potentially_lock_free) {
            _Check_alignment(_Value);
        } else {
            this->_Init_spinlock_for_ref();
        }
    }

    atomic_ref(const atomic_ref&) noexcept = default;

    atomic_ref& operator=(const atomic_ref&) = delete;

    static constexpr bool is_always_lock_free = _Is_always_lock_free<sizeof(_Ty)>;

    static constexpr bool _Is_potentially_lock_free =
        sizeof(_Ty) <= 2 * sizeof(void*) && (sizeof(_Ty) & (sizeof(_Ty) - 1)) == 0;

    static constexpr size_t required_alignment = _Is_potentially_lock_free ? sizeof(_Ty) : alignof(_Ty);

    _NODISCARD bool is_lock_free() const noexcept {
#if _ATOMIC_HAS_DCAS
        return is_always_lock_free;
#else // ^^^ _ATOMIC_HAS_DCAS / !_ATOMIC_HAS_DCAS vvv
        if constexpr (is_always_lock_free) {
            return true;
        } else {
            return __std_atomic_has_cmpxchg16b() != 0;
        }
#endif // _ATOMIC_HAS_DCAS
    }

    void store(const _Ty _Value) const noexcept {
        const_cast<atomic_ref*>(this)->_Base::store(_Value);
    }

    void store(const _Ty _Value, const memory_order _Order) const noexcept {
        const_cast<atomic_ref*>(this)->_Base::store(_Value, _Order);
    }

    _Ty operator=(const _Ty _Value) const noexcept {
        store(_Value);
        return _Value;
    }

    _Ty exchange(const _Ty _Value) const noexcept {
        return const_cast<atomic_ref*>(this)->_Base::exchange(_Value);
    }

    _Ty exchange(const _Ty _Value, const memory_order _Order) const noexcept {
        return const_cast<atomic_ref*>(this)->_Base::exchange(_Value, _Order);
    }

    bool compare_exchange_strong(_Ty& _Expected, const _Ty _Desired) const noexcept {
        return const_cast<atomic_ref*>(this)->_Base::compare_exchange_strong(_Expected, _Desired);
    }

    bool compare_exchange_strong(_Ty& _Expected, const _Ty _Desired, const memory_order _Order) const noexcept {
        return const_cast<atomic_ref*>(this)->_Base::compare_exchange_strong(_Expected, _Desired, _Order);
    }

    bool compare_exchange_strong(
        _Ty& _Expected, const _Ty _Desired, const memory_order _Success, const memory_order _Failure) const noexcept {
        return compare_exchange_strong(_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
    }

    bool compare_exchange_weak(_Ty& _Expected, const _Ty _Desired) const noexcept {
        return compare_exchange_strong(_Expected, _Desired);
    }

    bool compare_exchange_weak(_Ty& _Expected, const _Ty _Desired, const memory_order _Order) const noexcept {
        return compare_exchange_strong(_Expected, _Desired, _Order);
    }

    bool compare_exchange_weak(
        _Ty& _Expected, const _Ty _Desired, const memory_order _Success, const memory_order _Failure) const noexcept {
        return compare_exchange_strong(_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
    }

    operator _Ty() const noexcept {
        return this->load();
    }

    void notify_one() const noexcept {
        const_cast<atomic_ref*>(this)->_Base::notify_one();
    }

    void notify_all() const noexcept {
        const_cast<atomic_ref*>(this)->_Base::notify_all();
    }

private:
    static void _Check_alignment([[maybe_unused]] const _Ty& _Value) {
        _ATOMIC_REF_CHECK_ALIGNMENT(
            (reinterpret_cast<uintptr_t>(_STD addressof(_Value)) & (required_alignment - 1)) == 0,
            "atomic_ref underlying object is not aligned as required_alignment");
    }
};
#endif // _HAS_CXX20

template <class _Ty>
_NODISCARD bool atomic_is_lock_free(const volatile atomic<_Ty>* _Mem) noexcept {
    return _Mem->is_lock_free();
}

template <class _Ty>
_NODISCARD bool atomic_is_lock_free(const atomic<_Ty>* _Mem) noexcept {
    return _Mem->is_lock_free();
}

template <class _Ty>
void atomic_store(volatile atomic<_Ty>* const _Mem, const _Identity_t<_Ty> _Value) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    _Mem->store(_Value);
}

template <class _Ty>
void atomic_store(atomic<_Ty>* const _Mem, const _Identity_t<_Ty> _Value) noexcept {
    _Mem->store(_Value);
}

template <class _Ty>
void atomic_store_explicit(
    volatile atomic<_Ty>* const _Mem, const _Identity_t<_Ty> _Value, const memory_order _Order) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    _Mem->store(_Value, _Order);
}

template <class _Ty>
void atomic_store_explicit(atomic<_Ty>* const _Mem, const _Identity_t<_Ty> _Value, const memory_order _Order) noexcept {
    _Mem->store(_Value, _Order);
}

template <class _Ty>
_CXX20_DEPRECATE_ATOMIC_INIT void atomic_init(
    volatile atomic<_Ty>* const _Mem, const typename atomic<_Ty>::value_type _Value) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    _STD atomic_store_explicit(_Mem, _Value, memory_order_relaxed);
}

template <class _Ty>
_CXX20_DEPRECATE_ATOMIC_INIT void atomic_init(
    atomic<_Ty>* const _Mem, const typename atomic<_Ty>::value_type _Value) noexcept {
    _STD atomic_store_explicit(_Mem, _Value, memory_order_relaxed);
}

template <class _Ty>
_NODISCARD _Ty atomic_load(const volatile atomic<_Ty>* const _Mem) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->load();
}

template <class _Ty>
_NODISCARD _Ty atomic_load(const atomic<_Ty>* const _Mem) noexcept {
    return _Mem->load();
}

template <class _Ty>
_NODISCARD _Ty atomic_load_explicit(const volatile atomic<_Ty>* const _Mem, const memory_order _Order) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->load(_Order);
}

template <class _Ty>
_NODISCARD _Ty atomic_load_explicit(const atomic<_Ty>* const _Mem, const memory_order _Order) noexcept {
    return _Mem->load(_Order);
}

template <class _Ty>
_Ty atomic_exchange(volatile atomic<_Ty>* const _Mem, const _Identity_t<_Ty> _Value) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->exchange(_Value);
}

template <class _Ty>
_Ty atomic_exchange(atomic<_Ty>* const _Mem, const _Identity_t<_Ty> _Value) noexcept {
    return _Mem->exchange(_Value);
}

template <class _Ty>
_Ty atomic_exchange_explicit(
    volatile atomic<_Ty>* const _Mem, const _Identity_t<_Ty> _Value, const memory_order _Order) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->exchange(_Value, _Order);
}

template <class _Ty>
_Ty atomic_exchange_explicit(
    atomic<_Ty>* const _Mem, const _Identity_t<_Ty> _Value, const memory_order _Order) noexcept {
    return _Mem->exchange(_Value, _Order);
}

template <class _Ty>
bool atomic_compare_exchange_strong(
    volatile atomic<_Ty>* const _Mem, _Identity_t<_Ty>* const _Expected, const _Identity_t<_Ty> _Desired) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->compare_exchange_strong(*_Expected, _Desired);
}

template <class _Ty>
bool atomic_compare_exchange_strong(
    atomic<_Ty>* const _Mem, _Identity_t<_Ty>* const _Expected, const _Identity_t<_Ty> _Desired) noexcept {
    return _Mem->compare_exchange_strong(*_Expected, _Desired);
}

template <class _Ty>
bool atomic_compare_exchange_strong_explicit(volatile atomic<_Ty>* const _Mem, _Identity_t<_Ty>* const _Expected,
    const _Identity_t<_Ty> _Desired, const memory_order _Success, const memory_order _Failure) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->compare_exchange_strong(*_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
}

template <class _Ty>
bool atomic_compare_exchange_strong_explicit(atomic<_Ty>* const _Mem, _Identity_t<_Ty>* const _Expected,
    const _Identity_t<_Ty> _Desired, const memory_order _Success, const memory_order _Failure) noexcept {
    return _Mem->compare_exchange_strong(*_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
}

template <class _Ty>
bool atomic_compare_exchange_weak(
    volatile atomic<_Ty>* const _Mem, _Identity_t<_Ty>* const _Expected, const _Identity_t<_Ty> _Desired) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->compare_exchange_strong(*_Expected, _Desired);
}

template <class _Ty>
bool atomic_compare_exchange_weak(
    atomic<_Ty>* const _Mem, _Identity_t<_Ty>* const _Expected, const _Identity_t<_Ty> _Desired) noexcept {
    return _Mem->compare_exchange_strong(*_Expected, _Desired);
}

template <class _Ty>
bool atomic_compare_exchange_weak_explicit(volatile atomic<_Ty>* const _Mem, _Identity_t<_Ty>* const _Expected,
    const _Identity_t<_Ty> _Desired, const memory_order _Success, const memory_order _Failure) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->compare_exchange_strong(*_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
}

template <class _Ty>
bool atomic_compare_exchange_weak_explicit(atomic<_Ty>* const _Mem, _Identity_t<_Ty>* const _Expected,
    const _Identity_t<_Ty> _Desired, const memory_order _Success, const memory_order _Failure) noexcept {
    return _Mem->compare_exchange_strong(*_Expected, _Desired, _Combine_cas_memory_orders(_Success, _Failure));
}

template <class _Ty>
_Ty atomic_fetch_add(volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::difference_type _Value) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_add(_Value);
}

template <class _Ty>
_Ty atomic_fetch_add(atomic<_Ty>* _Mem, const typename atomic<_Ty>::difference_type _Value) noexcept {
    return _Mem->fetch_add(_Value);
}

template <class _Ty>
_Ty atomic_fetch_add_explicit(volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::difference_type _Value,
    const memory_order _Order) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_add(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_add_explicit(
    atomic<_Ty>* _Mem, const typename atomic<_Ty>::difference_type _Value, const memory_order _Order) noexcept {
    return _Mem->fetch_add(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_sub(volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::difference_type _Value) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_sub(_Value);
}

template <class _Ty>
_Ty atomic_fetch_sub(atomic<_Ty>* _Mem, const typename atomic<_Ty>::difference_type _Value) noexcept {
    return _Mem->fetch_sub(_Value);
}

template <class _Ty>
_Ty atomic_fetch_sub_explicit(volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::difference_type _Value,
    const memory_order _Order) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_sub(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_sub_explicit(
    atomic<_Ty>* _Mem, const typename atomic<_Ty>::difference_type _Value, const memory_order _Order) noexcept {
    return _Mem->fetch_sub(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_and(volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_and(_Value);
}

template <class _Ty>
_Ty atomic_fetch_and(atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value) noexcept {
    return _Mem->fetch_and(_Value);
}

template <class _Ty>
_Ty atomic_fetch_and_explicit(
    volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value, const memory_order _Order) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_and(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_and_explicit(
    atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value, const memory_order _Order) noexcept {
    return _Mem->fetch_and(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_or(volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_or(_Value);
}

template <class _Ty>
_Ty atomic_fetch_or(atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value) noexcept {
    return _Mem->fetch_or(_Value);
}

template <class _Ty>
_Ty atomic_fetch_or_explicit(
    volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value, const memory_order _Order) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_or(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_or_explicit(
    atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value, const memory_order _Order) noexcept {
    return _Mem->fetch_or(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_xor(volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_xor(_Value);
}

template <class _Ty>
_Ty atomic_fetch_xor(atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value) noexcept {
    return _Mem->fetch_xor(_Value);
}

template <class _Ty>
_Ty atomic_fetch_xor_explicit(
    volatile atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value, const memory_order _Order) noexcept {
    static_assert(_Deprecate_non_lock_free_volatile<_Ty>, "Never fails");
    return _Mem->fetch_xor(_Value, _Order);
}

template <class _Ty>
_Ty atomic_fetch_xor_explicit(
    atomic<_Ty>* _Mem, const typename atomic<_Ty>::value_type _Value, const memory_order _Order) noexcept {
    return _Mem->fetch_xor(_Value, _Order);
}

#if _HAS_CXX20
template <class _Ty>
void atomic_wait(const volatile atomic<_Ty>* const _Mem, const typename atomic<_Ty>::value_type _Expected) noexcept
/* strengthened */ {
    _Mem->wait(_Expected);
}

template <class _Ty>
void atomic_wait(const atomic<_Ty>* const _Mem, const typename atomic<_Ty>::value_type _Expected) noexcept
/* strengthened */ {
    _Mem->wait(_Expected);
}

template <class _Ty>
void atomic_wait_explicit(const volatile atomic<_Ty>* const _Mem, const typename atomic<_Ty>::value_type _Expected,
    const memory_order _Order) noexcept /* strengthened */ {
    _Mem->wait(_Expected, _Order);
}

template <class _Ty>
void atomic_wait_explicit(const atomic<_Ty>* const _Mem, const typename atomic<_Ty>::value_type _Expected,
    const memory_order _Order) noexcept /* strengthened */ {
    _Mem->wait(_Expected, _Order);
}

template <class _Ty>
void atomic_notify_one(volatile atomic<_Ty>* const _Mem) noexcept /* strengthened */ {
    _Mem->notify_one();
}

template <class _Ty>
void atomic_notify_one(atomic<_Ty>* const _Mem) noexcept /* strengthened */ {
    _Mem->notify_one();
}

template <class _Ty>
void atomic_notify_all(volatile atomic<_Ty>* const _Mem) noexcept /* strengthened */ {
    _Mem->notify_all();
}

template <class _Ty>
void atomic_notify_all(atomic<_Ty>* const _Mem) noexcept /* strengthened */ {
    _Mem->notify_all();
}
#endif // _HAS_CXX20

using atomic_bool = atomic<bool>;

using atomic_char   = atomic<char>;
using atomic_schar  = atomic<signed char>;
using atomic_uchar  = atomic<unsigned char>;
using atomic_short  = atomic<short>;
using atomic_ushort = atomic<unsigned short>;
using atomic_int    = atomic<int>;
using atomic_uint   = atomic<unsigned int>;
using atomic_long   = atomic<long>;
using atomic_ulong  = atomic<unsigned long>;
using atomic_llong  = atomic<long long>;
using atomic_ullong = atomic<unsigned long long>;

#ifdef __cpp_lib_char8_t
using atomic_char8_t = atomic<char8_t>;
#endif // __cpp_lib_char8_t
using atomic_char16_t = atomic<char16_t>;
using atomic_char32_t = atomic<char32_t>;
using atomic_wchar_t  = atomic<wchar_t>;

using atomic_int8_t   = atomic<int8_t>;
using atomic_uint8_t  = atomic<uint8_t>;
using atomic_int16_t  = atomic<int16_t>;
using atomic_uint16_t = atomic<uint16_t>;
using atomic_int32_t  = atomic<int32_t>;
using atomic_uint32_t = atomic<uint32_t>;
using atomic_int64_t  = atomic<int64_t>;
using atomic_uint64_t = atomic<uint64_t>;

using atomic_int_least8_t   = atomic<int_least8_t>;
using atomic_uint_least8_t  = atomic<uint_least8_t>;
using atomic_int_least16_t  = atomic<int_least16_t>;
using atomic_uint_least16_t = atomic<uint_least16_t>;
using atomic_int_least32_t  = atomic<int_least32_t>;
using atomic_uint_least32_t = atomic<uint_least32_t>;
using atomic_int_least64_t  = atomic<int_least64_t>;
using atomic_uint_least64_t = atomic<uint_least64_t>;

using atomic_int_fast8_t   = atomic<int_fast8_t>;
using atomic_uint_fast8_t  = atomic<uint_fast8_t>;
using atomic_int_fast16_t  = atomic<int_fast16_t>;
using atomic_uint_fast16_t = atomic<uint_fast16_t>;
using atomic_int_fast32_t  = atomic<int_fast32_t>;
using atomic_uint_fast32_t = atomic<uint_fast32_t>;
using atomic_int_fast64_t  = atomic<int_fast64_t>;
using atomic_uint_fast64_t = atomic<uint_fast64_t>;

using atomic_intptr_t  = atomic<intptr_t>;
using atomic_uintptr_t = atomic<uintptr_t>;
using atomic_size_t    = atomic<size_t>;
using atomic_ptrdiff_t = atomic<ptrdiff_t>;
using atomic_intmax_t  = atomic<intmax_t>;
using atomic_uintmax_t = atomic<uintmax_t>;

#if _HAS_CXX20
// Though there are CMPXCHG8B and CMPXCHG16B,
// the largest atomics with a full set of efficient operations are pointer-sized.
using atomic_signed_lock_free   = atomic_intptr_t;
using atomic_unsigned_lock_free = atomic_uintptr_t;
#endif // _HAS_CXX20

#define ATOMIC_FLAG_INIT \
    {}

struct atomic_flag { // flag with test-and-set semantics
#if _HAS_CXX20
    _NODISCARD bool test(const memory_order _Order = memory_order_seq_cst) const noexcept {
        return _Storage.load(_Order) != 0;
    }

    _NODISCARD bool test(const memory_order _Order = memory_order_seq_cst) const volatile noexcept {
        return _Storage.load(_Order) != 0;
    }
#endif // _HAS_CXX20

    bool test_and_set(const memory_order _Order = memory_order_seq_cst) noexcept {
        return _Storage.exchange(true, _Order) != 0;
    }

    bool test_and_set(const memory_order _Order = memory_order_seq_cst) volatile noexcept {
        return _Storage.exchange(true, _Order) != 0;
    }

    void clear(const memory_order _Order = memory_order_seq_cst) noexcept {
        _Storage.store(false, _Order);
    }

    void clear(const memory_order _Order = memory_order_seq_cst) volatile noexcept {
        _Storage.store(false, _Order);
    }

    constexpr atomic_flag() noexcept = default;

#if _HAS_CXX20
    void wait(const bool _Expected, const memory_order _Order = memory_order_seq_cst) const noexcept {
        _Storage.wait(static_cast<decltype(_Storage)::value_type>(_Expected), _Order);
    }

    void wait(const bool _Expected, const memory_order _Order = memory_order_seq_cst) const volatile noexcept {
        _Storage.wait(static_cast<decltype(_Storage)::value_type>(_Expected), _Order);
    }

    void notify_one() noexcept {
        _Storage.notify_one();
    }

    void notify_one() volatile noexcept {
        _Storage.notify_one();
    }

    void notify_all() noexcept {
        _Storage.notify_all();
    }

    void notify_all() volatile noexcept {
        _Storage.notify_all();
    }
#endif // _HAS_CXX20

#if 1 // TRANSITION, ABI
    atomic<long> _Storage;
#else // ^^^ don't break ABI / break ABI vvv
    atomic<bool> _Storage;
#endif // TRANSITION, ABI
};


#if _HAS_CXX20
_NODISCARD inline bool atomic_flag_test(const volatile atomic_flag* const _Flag) noexcept {
    return _Flag->test();
}

_NODISCARD inline bool atomic_flag_test(const atomic_flag* const _Flag) noexcept {
    return _Flag->test();
}

_NODISCARD inline bool atomic_flag_test_explicit(
    const volatile atomic_flag* const _Flag, const memory_order _Order) noexcept {
    return _Flag->test(_Order);
}

_NODISCARD inline bool atomic_flag_test_explicit(const atomic_flag* const _Flag, const memory_order _Order) noexcept {
    return _Flag->test(_Order);
}
#endif // _HAS_CXX20

inline bool atomic_flag_test_and_set(atomic_flag* const _Flag) noexcept {
    return _Flag->test_and_set();
}

inline bool atomic_flag_test_and_set(volatile atomic_flag* const _Flag) noexcept {
    return _Flag->test_and_set();
}

inline bool atomic_flag_test_and_set_explicit(atomic_flag* const _Flag, const memory_order _Order) noexcept {
    return _Flag->test_and_set(_Order);
}

inline bool atomic_flag_test_and_set_explicit(volatile atomic_flag* const _Flag, const memory_order _Order) noexcept {
    return _Flag->test_and_set(_Order);
}

inline void atomic_flag_clear(atomic_flag* const _Flag) noexcept {
    _Flag->clear();
}

inline void atomic_flag_clear(volatile atomic_flag* const _Flag) noexcept {
    _Flag->clear();
}

inline void atomic_flag_clear_explicit(atomic_flag* const _Flag, const memory_order _Order) noexcept {
    _Flag->clear(_Order);
}

inline void atomic_flag_clear_explicit(volatile atomic_flag* const _Flag, const memory_order _Order) noexcept {
    _Flag->clear(_Order);
}

#if _HAS_CXX20
inline void atomic_flag_wait(const volatile atomic_flag* const _Flag, const bool _Expected) noexcept {
    return _Flag->wait(_Expected);
}

inline void atomic_flag_wait(const atomic_flag* const _Flag, const bool _Expected) noexcept {
    return _Flag->wait(_Expected);
}

inline void atomic_flag_wait_explicit(
    const volatile atomic_flag* const _Flag, const bool _Expected, const memory_order _Order) noexcept {
    return _Flag->wait(_Expected, _Order);
}

inline void atomic_flag_wait_explicit(
    const atomic_flag* const _Flag, const bool _Expected, const memory_order _Order) noexcept {
    return _Flag->wait(_Expected, _Order);
}

inline void atomic_flag_notify_one(volatile atomic_flag* const _Flag) noexcept {
    return _Flag->notify_one();
}

inline void atomic_flag_notify_one(atomic_flag* const _Flag) noexcept {
    return _Flag->notify_one();
}

inline void atomic_flag_notify_all(volatile atomic_flag* const _Flag) noexcept {
    return _Flag->notify_all();
}

inline void atomic_flag_notify_all(atomic_flag* const _Flag) noexcept {
    return _Flag->notify_all();
}

template <class _Ty>
class _Locked_pointer {
public:
    static_assert(alignof(_Ty) >= (1 << 2), "2 low order bits are needed by _Locked_pointer");
    static constexpr uintptr_t _Lock_mask                = 3;
    static constexpr uintptr_t _Not_locked               = 0;
    static constexpr uintptr_t _Locked_notify_not_needed = 1;
    static constexpr uintptr_t _Locked_notify_needed     = 2;
    static constexpr uintptr_t _Ptr_value_mask           = ~_Lock_mask;

    constexpr _Locked_pointer() noexcept : _Storage{} {}
    explicit _Locked_pointer(_Ty* const _Ptr) noexcept : _Storage{reinterpret_cast<uintptr_t>(_Ptr)} {}

    _Locked_pointer(const _Locked_pointer&) = delete;
    _Locked_pointer& operator=(const _Locked_pointer&) = delete;

    _NODISCARD _Ty* _Lock_and_load() noexcept {
        uintptr_t _Rep = _Storage.load(memory_order_relaxed);
        for (;;) {
            switch (_Rep & _Lock_mask) {
            case _Not_locked: // Can try to lock now
                if (_Storage.compare_exchange_weak(_Rep, _Rep | _Locked_notify_not_needed)) {
                    return reinterpret_cast<_Ty*>(_Rep);
                }
                _YIELD_PROCESSOR();
                break;

            case _Locked_notify_not_needed: // Try to set "notify needed" and wait
                if (!_Storage.compare_exchange_weak(_Rep, (_Rep & _Ptr_value_mask) | _Locked_notify_needed)) {
                    // Failed to set notify needed flag, try again
                    _YIELD_PROCESSOR();
                    break;
                }
                _Rep = (_Rep & _Ptr_value_mask) | _Locked_notify_needed;
                [[fallthrough]];

            case _Locked_notify_needed: // "Notify needed" is already set, just wait
                _Storage.wait(_Rep, memory_order_relaxed);
                _Rep = _Storage.load(memory_order_relaxed);
                break;

            default: // Unrecognized bit pattern
                _CSTD abort();
            }
        }
    }

    void _Store_and_unlock(_Ty* const _Value) noexcept {
        const auto _Rep = _Storage.exchange(reinterpret_cast<uintptr_t>(_Value));
        if ((_Rep & _Lock_mask) == _Locked_notify_needed) {
            // As we don't count waiters, every waiter is notified, and then some may re-request notification
            _Storage.notify_all();
        }
    }

    _NODISCARD _Ty* _Unsafe_load_relaxed() const noexcept {
        return reinterpret_cast<_Ty*>(_Storage.load(memory_order_relaxed));
    }

private:
    atomic<uintptr_t> _Storage;
};
#endif // _HAS_CXX20

_STD_END

#undef _CMPXCHG_MASK_OUT_PADDING_BITS

#undef _ATOMIC_CHOOSE_INTRINSIC
#undef _ATOMIC_HAS_DCAS

#undef _STD_COMPARE_EXCHANGE_128
#undef _INVALID_MEMORY_ORDER
#undef _Compiler_or_memory_barrier
#undef _Memory_barrier
#undef _Compiler_barrier

#pragma pop_macro("new")
_STL_RESTORE_CLANG_WARNINGS
#pragma warning(pop)
#pragma pack(pop)
#endif // _STL_COMPILER_PREPROCESSOR
#endif // _ATOMIC_
