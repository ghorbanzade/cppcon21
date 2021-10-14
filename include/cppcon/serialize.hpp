#pragma once

#include <concepts>
#include <iostream>
#include <string>

#include "cppcon/common.hpp"

template <typename Test, template <typename...> class Ref>
struct is_specialization : std::false_type {};

template <template <typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

template <typename T, typename Enabled = void>
struct serializer {
  serialized_t serialize(T value) {
    static_assert(std::is_same<serialized_t, T>::value,
                  "did not find any specialization of serializer");
    return static_cast<T>(value);
  }
};

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(*std::declval<T>().begin()),
                                  decltype(*std::declval<T>().end())>>
    : std::true_type {};

template <typename T>
using is_null = std::is_same<T, std::nullptr_t>;

template <typename T>
using is_bool = std::is_same<T, bool>;

template <typename T>
using is_number = std::disjunction<
    std::conjunction<std::negation<is_bool<T>>, std::is_integral<T>>,
    std::conjunction<std::is_floating_point<T>>>;

template <typename T>
using is_string =
    std::conjunction<std::negation<is_null<T>>,
                     std::disjunction<std::is_constructible<std::string, T>,
                                      std::is_constructible<std::wstring, T>>>;

template <typename T>
using is_array = std::conjunction<std::negation<is_string<T>>, is_iterable<T>>;

template <typename T>
struct serializer<T, std::enable_if_t<is_null<T>::value>> {
  serialized_t serialize(const T& value) { return serialized_t(); }
};

template <typename T>
struct serializer<T, std::enable_if_t<is_bool<T>::value>> {
  serialized_t serialize(const T& value) {
    std::cout << value << std::endl;
    return serialized_t();
  }
};

template <typename T>
struct serializer<T, std::enable_if_t<is_number<T>::value>> {
  serialized_t serialize(const T& value) {
    std::cout << value << std::endl;
    return serialized_t();
  }
};

template <typename T>
struct serializer<T, std::enable_if_t<is_string<T>::value>> {
  serialized_t serialize(const T& value) {
    std::cout << value << std::endl;
    return serialized_t();
  }
};

template <typename T>
struct serializer<T, std::enable_if_t<is_array<T>::value>> {
  serialized_t serialize(const T& values) {
    for (const auto& v : values) {
      serializer<typename T::value_type>().serialize(v);
    }
    return serialized_t();
  }
};

template <typename T>
struct serializer<T, std::enable_if_t<is_specialization<T, std::pair>::value>> {
  serialized_t serialize(const T& value) {
    return detail::array()
        .add(serializer<typename T::first_type>().serialize(value.first))
        .add(serializer<typename T::second_type>().serialize(value.second));
  }
};

void check_impl(const std::string& key, const serialized_t& value) {
  std::cout << "check_impl called" << std::endl;
}

template <typename Char, typename Value>
void check(Char&& key, const Value& value) {
  check_impl(std::forward<Char>(key), serializer<Value>().serialize(value));
}
