#pragma once

template <typename T> void measure() {
  T::init();
  using namespace std::chrono;
  int sum = 0;
  int trial = 10000 / T::size();
  auto t0 = high_resolution_clock::now();
  for (int i = 0; i < trial; ++i) {
#define KEY_VALUE(k, v) sum += T::get(k, 0);
      KEY_VALUES_20
#undef KEY_VALUE
  }
  auto t1 = high_resolution_clock::now();
  auto tick = duration_cast<microseconds>(t1 - t0).count() * 1e-3;
  std::cout << "tick=" << tick << "  sum=" << sum << std::endl;
}
