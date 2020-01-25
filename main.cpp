#include <chrono>
#include <iostream>
#include <cstdlib>

#define KEY_VALUES KEY_VALUES_2
#define SIZE 2
#define NS size2
#include "defmap.hpp"
#undef NS
#undef SIZE
#undef KEY_VALUES

#define KEY_VALUES KEY_VALUES_20
#define SIZE 20
#define NS size20
#include "defmap.hpp"
#undef NS
#undef SIZE
#undef KEY_VALUES

#define KEY_VALUES KEY_VALUES_200
#define SIZE 200
#define NS size200
#include "defmap.hpp"
#undef NS
#undef SIZE
#undef KEY_VALUES

#define KEY_VALUES KEY_VALUES_2000
#define SIZE 2000
#define NS size2000
#include "defmap.hpp"
#undef NS
#undef SIZE
#undef KEY_VALUES

#include "measure.hpp"

int main(int argc, char const *argv[]) {
  int k = argc < 2 ? 0 : std::atoi(argv[1]);
  measure<size2::swith_case>("switch", k);
  measure<size2::map>("map", k);
  measure<size2::umap>("unordered_map", k);
  measure<size2::vmap>("vector_map", k);

  measure<size20::swith_case>("switch", k);
  measure<size20::map>("map", k);
  measure<size20::umap>("unordered_map", k);
  measure<size20::vmap>("vector_map", k);

  measure<size200::swith_case>("switch", k);
  measure<size200::map>("map", k);
  measure<size200::umap>("unordered_map", k);
  measure<size200::vmap>("vector_map", k);

  measure<size2000::swith_case>("switch", k);
  measure<size2000::map>("map", k);
  measure<size2000::umap>("unordered_map", k);
  measure<size2000::vmap>("vector_map", k);
  return 0;
}