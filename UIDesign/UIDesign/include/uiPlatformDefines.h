#pragma once

// Windows exclusive
#if defined(_DEBUG) || defined(DEBUG)
# define UI_DEBUG_MODE 1
#else
# define UI_DEBUG_MODE 0
#endif
