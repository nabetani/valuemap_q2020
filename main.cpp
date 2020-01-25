#include <chrono>
#include <iostream>

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

int main() {
  measure<size2::map>("map");
  measure<size2::umap>("unordered_map");
  measure<size2::vmap>("vector_map");

  measure<size20::map>("map");
  measure<size20::umap>("unordered_map");
  measure<size20::vmap>("vector_map");

  measure<size200::map>("map");
  measure<size200::umap>("unordered_map");
  measure<size200::vmap>("vector_map");

  measure<size2000::map>("map");
  measure<size2000::umap>("unordered_map");
  measure<size2000::vmap>("vector_map");
  return 0;
}