#include "uiMemoryAllocator.h"

UI_THREADLOCAL uint64 MemoryCounter::m_allocs = 0;
UI_THREADLOCAL uint64 MemoryCounter::m_frees = 0;