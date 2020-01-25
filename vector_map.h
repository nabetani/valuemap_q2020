#pragma once

template <typename key_type_, typename value_type_> struct vector_map {
  using key_type = key_type_;
  using value_type = value_type_;
  using key_value = std::pair<key_type, value_type>;
  using container_type = std::vector<key_value>;
  using const_iterator = typename container_type::const_iterator;
  using iterator = typename container_type::iterator;

  container_type container_;
  vector_map(std::initializer_list<key_value> const &kv) : container_(kv) {}

  iterator begin() { return container_.begin(); }
  const_iterator cbegin() const { return container_.cbegin(); }
  iterator end() { return container_.end(); }
  const_iterator cend() const { return container_.cend(); }

  const_iterator find(key_type const &key) const {
    return std::find_if(cbegin(), cend(), [&key](key_value const &kv) -> bool {
      return kv.first == key;
    });
  }
  iterator find(key_type const &key) {
    return std::find_if(begin(), end(), [&key](key_value const &kv) -> bool {
      return kv.first == key;
    });
  }
};
