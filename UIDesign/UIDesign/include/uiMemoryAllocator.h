#pragma once


#undef min
#undef max

// TODO: MOVE THIS
# define UI_THREADLOCAL __declspec(thread)
# define _NOEXCEPT noexcept

#include <new>
#include <atomic>
#include <utility>

#include "uiPlatformTypes.h"
#include "uiUtilities.h"

// using namespace functions
using std::forward;
using std::ptrdiff_t;

class MemoryAllocatorBase;

// WIN32
inline void*
PlatformAlignedAlloc16(SizeT size) {
  return _aligned_malloc(size, 16);
}

inline void
PlatformAlignedFree16(void* ptr) {
  _aligned_free(ptr);
}

inline void*
PlatformAlignedAlloc(SizeT size, SizeT alignment) {
  return _aligned_malloc(size, alignment);
}

inline void
PlatformAlignedFree(void* ptr) {
  _aligned_free(ptr);
}
// 

class MemoryCounter
{
public:
  static uint64
    GetNumAllocs() {
    return m_allocs;
  }

  static uint64
    GetNumFrees() {
    return m_frees;
  }

private:
  friend class MemoryAllocatorBase;

  /**
    * Thread local data can't be exported, so some magic to make it accessible
    * from MemoryAllocator
    */
  static void
  IncrementAllocCount() {
    ++m_allocs;
  }

  static void
  IncrementFreeCount() {
    ++m_frees;
  }

  static UI_THREADLOCAL uint64 m_allocs;
  static UI_THREADLOCAL uint64 m_frees;
};

class MemoryAllocatorBase
{
protected:
  static void
  IncrementAllocCount() {
    MemoryCounter::IncrementAllocCount();
  }

  static void
  IncrementFreeCount() {
    MemoryCounter::IncrementFreeCount();
  }
};

template<class T>
class MemoryAllocator : public MemoryAllocatorBase
{
public:
  static void*
    Allocate(SizeT bytes) {
#if UI_PROFILING_ENABLED
    IncrementAllocCount();
#endif
    return malloc(bytes);
  }

  /**
    * @brief Allocates @p bytes and aligns them to the specified boundary (in bytes).
    *        If the alignment is less or equal to 16 it is more efficient to use the
    *        allocateAligned16() alternative of this method.
    *        Alignment must be power of two.
    */
  static void*
    AllocateAligned(SizeT bytes, SizeT alignment) {
#if UI_PROFILING_ENABLED
    IncrementAllocCount();
#endif
    return PlatformAlignedAlloc(bytes, alignment);
  }

  /**
    * @brief Allocates @p bytes and aligns them to a 16 byte boundary.
    */
  static void*
    AllocateAligned16(SizeT bytes) {
#if UI_PROFILING_ENABLED
    IncrementAllocCount();
#endif
    return PlatformAlignedAlloc16(bytes);
  }

  static void
    Free(void* ptr) {
#if UI_PROFILING_ENABLED
    IncrementFreeCount();
#endif
    ::free(ptr);
  }

  /**
    * @brief Frees memory allocated with allocateAligned()
    */
  static void
    FreeAligned(void* ptr) {
#if UI_PROFILING_ENABLED
    IncrementFreeCount();
#endif
    PlatformAlignedFree(ptr);
  }

  /**
    * @brief Frees memory allocated with allocateAligned16()
    */
  static void
    FreeAligned16(void* ptr) {
#if UI_PROFILING_ENABLED
    IncrementFreeCount();
#endif
    PlatformAlignedFree16(ptr);
  }
};

class GenAlloc
{};

/**
  * @brief Allocates the specified number of bytes.
  */
template<class Alloc>
inline void*
Ui_alloc(SizeT count) {
  return MemoryAllocator<Alloc>::Allocate(count);
}

/**
  * @brief Allocates enough bytes to hold the specified type, but doesn't construct it.
  */
template<class T, class Alloc>
inline T*
Ui_alloc() {
  return reinterpret_cast<T*>(MemoryAllocator<Alloc>::Allocate(sizeof(T)));
}

/**
  * @brief Creates and constructs an array of "count" elements.
  */
template<class T, class Alloc>
inline T*
Ui_newN(SizeT count) {
  auto ptr = reinterpret_cast<T*>(MemoryAllocator<Alloc>::Allocate(sizeof(T) * count));

  for (SizeT i = 0; i < count; ++i) {
    new (&ptr[i]) T;
  }

  return ptr;
}


/**
  * @brief Create a new object with the specified allocator and the specified parameters.
  */
template<class T, class Alloc, class... Args>
T*
Ui_new(Args&& ...args) {
  return new (Ui_alloc<T, Alloc>()) T(forward<Args>(args)...);
}

/**
  * @brief Frees all the bytes allocated at the specified location.
  */
template<class Alloc>
inline void
Ui_free(void* ptr) {
  MemoryAllocator<Alloc>::Free(ptr);
}

/**
  * @brief Destructs and frees the specified object.
  */
template<class T, class Alloc = GenAlloc>
inline void
Ui_delete(T* ptr) {
  (ptr)->~T();
  MemoryAllocator<Alloc>::Free(ptr);
}

/**
  * @brief Destructs and frees the specified array of objects.
  */
template<class T, class Alloc = GenAlloc>
inline void
Ui_deleteN(T* ptr, SizeT count) {
  for (SizeT i = 0; i < count; ++i) {
    ptr[i].~T();
  }
  MemoryAllocator<Alloc>::Free(ptr);
}


/**
* @brief Allocates the specified number of bytes.
*/
inline void*
Ui_alloc(SizeT count) {
  return MemoryAllocator<GenAlloc>::Allocate(count);
}

/**
  * @brief Allocates enough bytes to hold the specified type, but doesn't construct it.
  */
template<class T>
inline T*
Ui_alloc() {
  return reinterpret_cast<T*>(MemoryAllocator<GenAlloc>::Allocate(sizeof(T)));
}

/**
  * @brief Allocates the specified number of bytes aligned to the provided boundary.
  *        Boundary is in bytes and must be a power of two.
  */
inline void*
Ui_alloc_aligned(SizeT count, SizeT align) {
  return MemoryAllocator<GenAlloc>::AllocateAligned(count, align);
}

/**
  * @brief Allocates the specified number of bytes aligned to a 16 bytes boundary.
  */
inline void*
Ui_alloc_aligned16(SizeT count) {
  return MemoryAllocator<GenAlloc>::AllocateAligned16(count);
}

/**
  * @brief Creates and constructs an array of "count" elements.
  */
template<class T>
inline T*
Ui_allocN(SizeT count) {
  return reinterpret_cast<T*>(MemoryAllocator<GenAlloc>::Allocate(sizeof(T) * count));
}

/**
* @brief Creates and constructs an array of "count" elements.
*/
template<class T>
inline T*
Ui_newN(SizeT count) {
  T* ptr = reinterpret_cast<T*>(MemoryAllocator<GenAlloc>::Allocate(sizeof(T) * count));
  for (SizeT i = 0; i < count; ++i) {
    new (&ptr[i]) T;
  }

  return ptr;
}

/**
  * @brief Create a new object with the specified allocator and the specified parameters.
  */
template<class T, class... Args>
T*
Ui_new(Args&& ...args) {
  return new (Ui_alloc<T, GenAlloc>()) T(forward<Args>(args)...);
}

/**
  * @brief Frees all the bytes allocated at the specified location.
  */
inline void
Ui_free(void* ptr) {
  MemoryAllocator<GenAlloc>::Free(ptr);
}

/**
  * @brief Frees memory previously allocated with ge_alloc_aligned().
  */
inline void
Ui_free_aligned(void* ptr) {
  MemoryAllocator<GenAlloc>::FreeAligned(ptr);
}

/**
  * @brief Frees memory previously allocated with ge_alloc_aligned16().
  */
inline void
Ui_free_aligned16(void* ptr) {
  MemoryAllocator<GenAlloc>::FreeAligned16(ptr);
}


/***************************************************************************/
/**                     MACRO VERSIONS
  * You will almost always want to use the template versions but in some cases
  * (private constructor / destructor) it is not possible. In which case you
  * may use these instead.
  */
  /***************************************************************************/
#define CY_PVT_NEW(T, ...)                                                      \
  new (Ui_alloc<T, GenAlloc>()) T(__VA_ARGS__)

#define CY_PVT_DELETE(T, ptr)                                                   \
  (ptr)->~T();                                                                  \
  MemoryAllocator<GenAlloc>::Free(ptr);

#define CY_PVT_DELETE_A(T, ptr, Alloc)                                          \
  (ptr)->~T();                                                                  \
  MemoryAllocator<Alloc>::Free(ptr);

/**
  * @brief Allocator for the standard library that internally uses the
  *        Genesis Engine memory allocator.
  */
template <class T, class Alloc = GenAlloc>
class StdAlloc
{
public:
  using value_type = T;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = SizeT;
  using difference_type = ptrdiff_t;

  constexpr StdAlloc() = default;
  constexpr StdAlloc(StdAlloc&&) = default;
  constexpr StdAlloc(const StdAlloc&) = default;

  template<class U, class Alloc2>
  constexpr StdAlloc(const StdAlloc<U, Alloc2>&) _NOEXCEPT {}

  template<class U, class Alloc2>
  constexpr bool
    operator==(const StdAlloc<U, Alloc2>&) const _NOEXCEPT {
    return true;
  }

  template<class U, class Alloc2>
  constexpr bool
    operator!=(const StdAlloc<U, Alloc2>&) const _NOEXCEPT {
    return false;
  }

  template<class U>
  class rebind
  {
  public:
    using other = StdAlloc<U, Alloc>;
  };

  /**
    * @brief Allocate but don't initialize number elements of type T.
    */
  static T*
    Allocate(const SizeT num) {
    if (0 == num) {
      return nullptr;
    }

    if (num > NumericLimits<SizeT>::max() / sizeof(T)) {
      throw nullptr;
    }

    void* const pv = Ui_alloc<Alloc>(num * sizeof(T));
    if (!pv) {
      return nullptr;
    }

    return static_cast<T*>(pv);
  }

  /**
    * @brief Deallocate storage p of deleted elements.
    */
  static void
    deallocate(pointer p, SizeT) {
    Ui_free<Alloc>(p);
  }

  static constexpr SizeT
    max_size() {
    return NumericLimits<SizeT>::max() / sizeof(T);
  }

  static constexpr void
    destroy(pointer p) {
    p->~T();
  }

  /**
    * @brief This version of construct() (with a varying number of parameters)
    *        seems necessary in order to use some STL data structures from
    *        libstdc++-4.8, but compilation fails on OSX, hence the #if.
    */
  template<class... Args>
  static void
    construct(pointer p, Args&& ...args) {
    new(p) T(forward<Args>(args)...);
  }
};

