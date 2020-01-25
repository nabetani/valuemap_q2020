#include <chrono>
#include <iostream>

#include "defmap.hpp"
#include "measure.hpp"

int main() {
  measure<map20>();
  measure<umap20>();
  measure<vmap20>();
  return 0;
}