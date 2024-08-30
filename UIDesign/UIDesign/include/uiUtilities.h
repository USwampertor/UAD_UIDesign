#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <filesystem>
#include <functional>
#include <list>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <stack>
#include <type_traits>
#include <utility> 
#include <vector>
#include <string>

#include "uiPlatformTypes.h"

#include <SFML/System/Vector2.hpp>

#define NOMINMAX

#define RAPIDJSON_HAS_STDSTRING 1

// STD OBJECTS

using DirectoryEntry = std::filesystem::directory_entry;

template<typename T>
using Hash = std::hash<T>;

template<typename T, typename A = std::allocator<T>>
using List = std::list<T, A>;

template< typename KEY,
          typename T,
          typename B = std::less<KEY>,
          typename A = std::allocator<std::pair<const KEY, T>>>
using Map = std::map<KEY, T, B, A>;

template<typename T>
using NumericLimits = std::numeric_limits<T>;

template<typename T, typename A = std::deque<T>>
using Queue = std::queue<T, A>;

template<typename T, typename A>
using Pair = std::pair<T, A>;

using Path = std::filesystem::path;

using RunTimeError = std::runtime_error;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T, typename A = std::deque<T>>
using Stack = std::stack<T, A>;

using StdException = std::exception;

using String = std::string;

template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

using WString = std::string;


// SFML OBJECTS

using Vector2f = sf::Vector2f;

// FUNCTIONS

template <typename T, typename... Args>
UniquePtr<T> MakeUniqueObject(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
SharedPtr<T> MakeSharedObject(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// UTILITIES



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
  static String Format(const String& format, Args ... args) {
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { ThrowRuntimeError("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return String(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
  }

  template<typename T>
  static String 
  ToString(const T& number) {
    return std::to_string(number);
  }

  static void 
  ThrowException(const String& message) {
    throw::std::exception(message.c_str());
  }

  static void 
  ThrowRuntimeError(const String& message) {
    throw::std::runtime_error(message.c_str());
  }

  static const String BLANK;

  static WString
  ToWide(String str) {
    WString stemp = WString(str.begin(), str.end());
    return stemp;

  }

  template<typename T, typename A>
  static Pair<T, A>
  MakePair(T value1, A value2) {
    return std::make_pair(value1, value2);
  }
};