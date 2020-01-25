#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

template< template< typename, typename > typename map_t >
struct map20t {
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

template< typename k, typename v >
using unordered_map_ = std::unordered_map<k,v>;
using umap20 = map20t<unordered_map_>;
template<>
umap20::map_type umap20::values_={};

template< typename k, typename v >
using map_ = std::map<k,v>;
using map20 = map20t<map_>;
template<>
map20::map_type map20::values_={};


template <typename T> void measure() {
  T::init();
  using namespace std::chrono;
  int sum = 0;
  int trial = 10000/20;
  auto t0 = high_resolution_clock::now();
  for( int i=0 ; i<trial; ++i ){
    #define KEY_VALUE(k, v) sum += T::get(k, 0);
    #include "values_20.hxx"
    #undef KEY_VALUE
  }
  auto t1 = high_resolution_clock::now();
  auto tick = duration_cast<microseconds>( t1-t0 ).count() * 1e-3;
  std::cout << "tick=" << tick << "  sum=" << sum << std::endl;

}

int main() {
  measure<map20>();
  measure<umap20>();
  return 0;
}