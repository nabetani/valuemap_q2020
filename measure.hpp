#pragma once

#include <cstdio>

template <typename T> void measure(char const *name, int diff) {
  T::init();
  using namespace std::chrono;
  int sum = 0;
  int trial = 10000 / T::size();
  auto t0 = high_resolution_clock::now();
#define KEY_VALUE(k, v) sum += T::get(k + diff, 0);
#define TRIAL_LOOP(count, kv) \
  if constexpr (T::size() == count) {\
    for (int i = 0; i < trial; ++i) {\
      kv\
    }\
  }\

TRIAL_LOOP(3, KEY_VALUES_3)
TRIAL_LOOP(10, KEY_VALUES_10)
TRIAL_LOOP(30, KEY_VALUES_30)
TRIAL_LOOP(100, KEY_VALUES_100)
TRIAL_LOOP(300, KEY_VALUES_300)
TRIAL_LOOP(1000, KEY_VALUES_1000)
#undef KEY_VALUE
auto t1 = high_resolution_clock::now();
auto tick = duration_cast<microseconds>(t1 - t0).count() * 1e-3;
std::printf("%15s: %5zu tick=%7.3f  sum=%d\n", name, T::size(), tick, sum);
}
