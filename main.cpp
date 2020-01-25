#include <chrono>
#include <iostream>
#include <cstdlib>

#if ! defined CONCAT_MACRO_IMPL
#define CONCAT_MACRO_IMPL(a,b) a##b
#endif

#if ! defined CONCAT_MACRO
#define CONCAT_MACRO(a,b) CONCAT_MACRO_IMPL(a,b)
#endif

#define SIZE 3
#include "defmap.hpp"
#undef SIZE

#define SIZE 10
#include "defmap.hpp"
#undef SIZE

#define SIZE 30
#include "defmap.hpp"
#undef SIZE

#define SIZE 100
#include "defmap.hpp"
#undef SIZE

#define SIZE 300
#include "defmap.hpp"
#undef SIZE

// #define SIZE 1000
// #include "defmap.hpp"
// #undef SIZE

#include "measure.hpp"

int main(int argc, char const *argv[]) {
  int k = argc < 2 ? 0 : std::atoi(argv[1]);
  #define MEASURE(s)\
  measure<CONCAT_MACRO(size,s)::swith_case>("switch", k);\
  measure<CONCAT_MACRO(size,s)::map>("map", k);\
  measure<CONCAT_MACRO(size,s)::umap>("unordered_map", k);\
  measure<CONCAT_MACRO(size,s)::vmap>("vector_map", k);

  MEASURE(3)
  MEASURE(10)
  MEASURE(30)
  MEASURE(100)
  MEASURE(300)
  // MEASURE(1000)

  return 0;
}