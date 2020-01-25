#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>

#include "values.hxx"
#include "vector_map.h"

#define NS CONCAT_MACRO(size,SIZE)
#define KEY_VALUES CONCAT_MACRO(KEY_VALUES_, SIZE)

namespace NS {
template <template <typename, typename> typename map_t> struct mapt {
  static constexpr size_t size() { return SIZE; }
  using map_type = map_t<int, int>;
  static map_type values_;
  static void init() {
    values_ = map_type{
#define KEY_VALUE(k, v) {k, v},
        KEY_VALUES
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
using umap = mapt<unordered_map_>;
template <> umap::map_type umap::values_ = {};

template <typename k, typename v> using map_ = std::map<k, v>;
using map = mapt<map_>;
template <> map::map_type map::values_ = {};

using vmap = mapt<vector_map>;
template <> vmap::map_type vmap::values_ = {};

struct swith_case {
  static constexpr size_t size() { return SIZE; }
  static void init() {}
  static int get(int key, int fallback) {
    switch (key) {
#define KEY_VALUE(k, v) case k: return v;
        KEY_VALUES
#undef KEY_VALUE
    }
    return fallback;
  }
};

} // namespace NS

#undef NS
#undef KEY_VALUES

