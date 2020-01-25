#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

template <typename key_type_, typename value_type_> struct vector_map {
  using key_type = key_type_;
  using value_type = value_type_;
  using key_value = std::pair<key_type, value_type>;
  using container_type = std::vector<key_value>;
  using const_iterator = typename container_type::const_iterator;
  using iterator = typename container_type::iterator;

  container_type container_;
  vector_map(std::initializer_list<key_value> const &kv) : container_(kv) {}

  iterator begin() { return container_.begin(); }
  const_iterator cbegin() const { return container_.cbegin(); }
  iterator end() { return container_.end(); }
  const_iterator cend() const { return container_.cend(); }

  const_iterator find(key_type const &key) const {
    return std::find_if(cbegin(), cend(), [&key](key_value const &kv) -> bool {
      return kv.first == key;
    });
  }
  iterator find(key_type const &key) {
    return std::find_if(begin(), end(), [&key](key_value const &kv) -> bool {
      return kv.first == key;
    });
  }
};

template <template <typename, typename> typename map_t> struct map20t {
  using map_type = map_t<int, int>;
  static map_type values_;
  static void init() {
    values_ = map_type{
#define KEY_VALUE(k, v) {k, v},
#include "values_20.hxx"
#undef KEY_VALUE
    };
  }
  static int get(int key, int fallback) {
    auto it = values_.find(key);
    if (it == values_.end()) {
      return fallback;
    }
    return it->second;
  }
};

template <typename k, typename v>
using unordered_map_ = std::unordered_map<k, v>;
using umap20 = map20t<unordered_map_>;
template <> umap20::map_type umap20::values_ = {};

template <typename k, typename v> using map_ = std::map<k, v>;
using map20 = map20t<map_>;
template <> map20::map_type map20::values_ = {};

using vmap20 = map20t<vector_map>;
template <> vmap20::map_type vmap20::values_ = {};

template <typename T> void measure() {
  T::init();
  using namespace std::chrono;
  int sum = 0;
  int trial = 10000 / 20;
  auto t0 = high_resolution_clock::now();
  for (int i = 0; i < trial; ++i) {
#define KEY_VALUE(k, v) sum += T::get(k, 0);
#include "values_20.hxx"
#undef KEY_VALUE
  }
  auto t1 = high_resolution_clock::now();
  auto tick = duration_cast<microseconds>(t1 - t0).count() * 1e-3;
  std::cout << "tick=" << tick << "  sum=" << sum << std::endl;
}

int main() {
  measure<map20>();
  measure<umap20>();
  measure<vmap20>();
  return 0;
}