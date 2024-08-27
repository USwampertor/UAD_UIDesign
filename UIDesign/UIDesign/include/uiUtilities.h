#pragma once

#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <string>

#include <cmath>
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

template<typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;

using String = std::string;
