#pragma once

// STD
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <exception>
#include <filesystem>
#include <functional>
#include <fstream>
#include <iostream>
#include <list>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <stack>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility> 
#include <vector>


#define NOMINMAX

#define RAPIDJSON_HAS_STDSTRING 1

// STD OBJECTS

/**
 * @brief Wrapping of c++ std::array
 */
template<typename T, SizeT _Size>
using Array = std::array<T, _Size>;

/**
 * @brief Wrapping of c++ std::function as callback with raw data
 */
 // using Callback = std::function<void(void*)>;

template<typename ReturnType, typename... Args>
using Callback = std::function<ReturnType(Args...)>;

using DirectoryEntry = std::filesystem::directory_entry;

/**
 * @brief Wrapping of c++ std::exception
 */
using Exception = std::exception;

template<typename T>
using Hash = std::hash<T>;

template<typename T, typename A = std::allocator<T>>
using List = std::list<T, A>;

template< typename KEY,
  typename T,
  typename B = std::less<KEY>,
  typename A = std::allocator<std::pair<const KEY, T>>>
using Map = std::map<KEY, T, B, A>;

/**
 * @brief Wrapping of c++ std::mutex
 */
using Mutex = std::mutex;

template<typename T>
using NumericLimits = std::numeric_limits<T>;

template<typename T, typename A = std::deque<T>>
using Queue = std::queue<T, A>;

template<typename T, typename A>
using Pair = std::pair<T, A>;

using Path = std::filesystem::path;

/**
 * @brief Wrapping of c++ std::recursive_mutex
 */
using RecursiveMutex = std::recursive_mutex;

/**
 * @brief Wrapping of c++ std::unique_lock<RecursiveMutex>
 */
using RecursiveLock = std::unique_lock<RecursiveMutex>;

using RunTimeError = std::runtime_error;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T, typename A = std::deque<T>>
using Stack = std::stack<T, A>;

using StdException = std::exception;

using SStream = std::stringstream;

using String = std::string;

/**
 * @brief Wrapping of c++ std::thread
 */
using Thread = std::thread;

template<typename T, typename A>
using Tuple = std::tuple<T, A>;

/**
 * @brief Wrapping of c++ std::unique_lock<Mutex>
 */
using UniqueLock = std::unique_lock<Mutex>;

template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

using WString = std::string;

using FStream = std::fstream;

using IFStream = std::ifstream;

using OFStream = std::ofstream;
