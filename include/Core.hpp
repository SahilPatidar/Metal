#pragma once
#include <cassert>
#include <charconv>
#include <cstdint>
#include <cstring>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>

namespace ast {
using StringRef = std::string_view;
using String = std::string;
template<typename T> using Vec = std::vector<T>;
template<typename T> using List = std::forward_list<T>;
template<typename T> using InitList = std::initializer_list<T>;
template<typename K, typename V> using Map = std::map<K, V>;
}