#pragma once

struct serialized_t;

namespace detail {
struct array {
  array& add(const serialized_t& value) { return *this; }
};
}  // namespace detail

struct serialized_t {
  serialized_t() = default;
  serialized_t(const detail::array& value) : _value(false){};

 private:
  bool _value;
};
