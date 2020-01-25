#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>

#include "values.hxx"
#include "vector_map.h"

template <template <typename, typename> typename map_t> struct map20t {
  static constexpr size_t size() { return 20; }
  using map_type = map_t<int, int>;
  static map_type values_;
  static void init() {
    values_ = map_type{
#define KEY_VALUE(k, v) {k, v},
        KEY_VALUES_20
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
