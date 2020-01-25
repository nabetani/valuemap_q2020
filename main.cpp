#include <chrono>
#include <iostream>

#include "defmap.hpp"

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