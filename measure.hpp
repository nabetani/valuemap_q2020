#pragma once

#include <cstdio>

template <typename T> void measure(char const *name) {
  T::init();
  using namespace std::chrono;
  int sum = 0;
  int trial = 10000 / T::size();
  auto t0 = high_resolution_clock::now();
  if constexpr (T::size() == 2) {
    for (int i = 0; i < trial; ++i) {
#define KEY_VALUE(k, v) sum += T::get(k, 0);
      KEY_VALUES_2
#undef KEY_VALUE
    }
  }
  if constexpr (T::size() == 20) {
    for (int i = 0; i < trial; ++i) {
#define KEY_VALUE(k, v) sum += T::get(k, 0);
      KEY_VALUES_20
#undef KEY_VALUE
    }
  }
  if constexpr (T::size() == 200) {
    for (int i = 0; i < trial; ++i) {
#define KEY_VALUE(k, v) sum += T::get(k, 0);
      KEY_VALUES_200
#undef KEY_VALUE
    }
  }
  if constexpr (T::size() == 2000) {
    for (int i = 0; i < trial; ++i) {
#define KEY_VALUE(k, v) sum += T::get(k, 0);
      KEY_VALUES_2000
#undef KEY_VALUE
    }
  }
  auto t1 = high_resolution_clock::now();
  auto tick = duration_cast<microseconds>(t1 - t0).count() * 1e-3;
  std::printf("%15s: %5zu tick=%7.3f  sum=%d\n", name, T::size(), tick, sum);
}
