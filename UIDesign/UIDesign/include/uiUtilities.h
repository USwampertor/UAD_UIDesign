#pragma once

#include <cmath>
#include <filesystem>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <utility> 
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

template<typename T, typename A>
using Pair = std::pair<T, A>;

using Path = std::filesystem::path;

using DirectoryEntry = std::filesystem::directory_entry;

using int32 = int32_t;

struct FileSystem
{
  
  static const Path CurrentPath() { return std::filesystem::current_path(); }
  static void SetCurrentPath(const Path& p) { return std::filesystem::current_path(p); }

};

struct Utils
{
  static void
  runCommand(const String& commandLine) {
    system(commandLine.c_str());
  }

  template<typename ... Args>
  static String format(const String& format, Args ... args) {
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throwRuntimeError("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return String(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
  }

  template<typename T>
  static String 
  toString(const T& number) {
    return std::to_string(number);
  }

  static void 
  throwException(const String& message) {
    throw::std::exception(message.c_str());
  }

  static void 
  throwRuntimeError(const String& message) {
    throw::std::runtime_error(message.c_str());
  }

  static const String BLANK;

  static WString
  toWide(String str) {
    WString stemp = WString(str.begin(), str.end());
    return stemp;

  }

  template<typename T, typename A>
  static Pair<T, A>
  makePair(T value1, A value2) {
    return std::make_pair(value1, value2);
  }
};