#include<string>
#include<vector>
#include<map>

namespace ast {
using StringRef = std::string_view;
using String = std::string;
template<typename T> using Vector = std::vector<T>;
template<typename T> using String = std::string<T>;
template<typename K, typename V> using Map = std::map<K, V>;
}