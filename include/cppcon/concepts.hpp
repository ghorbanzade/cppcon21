#pragma once

#include <concepts>
#include <iostream>
#include <string>

#include "cppcon/common.hpp"

template <typename T>
concept Container = requires(T a, const T b) {
  requires std::regular<T>;
  requires std::swappable<T>;
  requires std::destructible<typename T::value_type>;
  requires std::same_as<typename T::reference, typename T::value_type&>;
  requires std::same_as<typename T::const_reference,
                        const typename T::value_type&>;
  requires std::forward_iterator<typename T::iterator>;
  requires std::forward_iterator<typename T::const_iterator>;
  requires std::signed_integral<typename T::difference_type>;
  requires std::same_as<
      typename T::difference_type,
      typename std::iterator_traits<typename T::iterator>::difference_type>;
  requires std::same_as<typename T::difference_type,
                        typename std::iterator_traits<
                            typename T::const_iterator>::difference_type>;
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
  { b.begin() } -> std::same_as<typename T::const_iterator>;
  { b.end() } -> std::same_as<typename T::const_iterator>;
  { a.cbegin() } -> std::same_as<typename T::const_iterator>;
  { a.cend() } -> std::same_as<typename T::const_iterator>;
  { a.size() } -> std::same_as<typename T::size_type>;
  { a.max_size() } -> std::same_as<typename T::size_type>;
  { a.empty() } -> std::same_as<bool>;
};

template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

template <typename T>
concept StringLike =
    std::convertible_to<T, std::basic_string<typename T::value_type>>;

template <typename T>
concept ArrayLike = !StringLike<T> && Container<T>;

template <typename T>
concept Serializable = requires(const T& x) {
  { x.serialize() } -> std::same_as<serialized_t>;
};

serialized_t serialize2(std::nullptr_t value) { return serialized_t(); }

serialized_t serialize2(const bool value) { return serialized_t(); }

serialized_t serialize2(const Arithmetic auto& value) { return serialized_t(); }

template <typename Char, std::size_t N>
serialized_t serialize2(const Char (&value)[N]) {
  return serialized_t();
}

serialized_t serialize2(const StringLike auto& value) { return serialized_t(); }

serialized_t serialize2(const ArrayLike auto& values) {
  for (const auto& v : values) {
    serialize2(v);
  }
  return serialized_t();
}

serialized_t serialize2(const Serializable auto& value) {
  return value.serialize();
}

template <typename T>
serialized_t serialize2(const T& value) {
  static_assert(std::is_same_v<serialized_t, T>,
                "did not find any serializer for the given type");
  return static_cast<T>(value);
}

void check_impl2(const std::string& key, const serialized_t& value) {
  std::cout << "check_impl2 called" << std::endl;
}

template <typename Char, typename Value>
void check2(Char&& key, const Value& value) {
  check_impl2(std::forward<Char>(key), serialize2(value));
}
