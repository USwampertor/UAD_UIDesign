#pragma once

#include <cmath>
#include <filesystem>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <string>

#define NOMINMAX


template<typename T, typename A = std::allocator<T>>
using List = std::list<T, A>;

template< typename KEY,
          typename T,
          typename B = std::less<KEY>,
          typename A = std::allocator<std::pair<const KEY, T>>>
using Map = std::map<KEY, T, B, A>;

template<typename T, typename A = std::deque<T>>
using Queue = std::queue<T, A>;

template<typename T, typename A = std::deque<T>>
using Stack = std::stack<T, A>;

using String = std::string;

using WString = std::string;

template<typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;

using Path = std::filesystem::path;

using DirectoryEntry = std::filesystem::directory_entry;

struct FileSystem
{
  
  static const Path CurrentPath() { return std::filesystem::current_path(); }
  static void SetCurrentPath(const Path& p) { return std::filesystem::current_path(p); }

};