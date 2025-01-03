#pragma once

// Windows exclusive
#if defined(_DEBUG) || defined(DEBUG)
# define UI_DEBUG_MODE 1
#else
# define UI_DEBUG_MODE 0
#endif

static bool g_isEditor;

#if UI_DEBUG_MODE
#define UI_EDITOR_MODE 1
#endif

#ifndef USE_STD_FILESYSTEM
#define USE_STD_FILESYSTEM
#endif

