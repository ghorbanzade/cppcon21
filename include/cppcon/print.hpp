#pragma once

#include <concepts>
#include <iostream>
#include <string>

#include "cppcon/date.hpp"
#include "fmt/printf.h"

template <typename T>
void print1(T arg) {
  std::cout << "Generic: " << arg << std::endl;
}

template <>
void print1(MyDate date) {
  std::cout << "Specialization: " << date.to_string() << std::endl;
}

void print2(auto arg) { std::cout << "Generic: " << arg << std::endl; }

void print2(MyDate arg) {
  std::cout << "Specialization: " << arg.to_string() << std::endl;
}

template <typename T>
struct printer1 {
  void print(T arg) { std::cout << "Generic: " << arg << std::endl; }
};

template <>
struct printer1<MyDate> {
  void print(MyDate arg) {
    std::cout << "Specialization: " << arg.to_string() << std::endl;
  }
};

template <typename Key, typename Value>
struct printer2 {
  void print(Key key, Value value) {
    std::cout << key << "Generic: " << value << std::endl;
  }
};

template <typename Key>
struct printer2<Key, MyDate> {
  void print(Key key, MyDate value) {
    std::cout << key << "Specialization: " << value.to_string() << std::endl;
  }
};

template <typename T, typename Enabled = void>
struct printer3 {
  void print(T value) { std::cout << "Generic: " << value << std::endl; }
};

template <typename T>
struct printer3<T,
                typename std::enable_if<std::is_same<T, MyDate>::value>::type> {
  void print(T value) {
    std::cout << "Specialization: " << value.to_string() << std::endl;
  }
};

template <typename T>
concept IsDate = std::is_same_v<T, MyDate>;

template <typename T>
concept IsNumeric = std::is_arithmetic_v<T>;

void printer4(auto value) { std::cout << "Generic: " << value << std::endl; }

void printer4(IsDate auto value) {
  std::cout << "Specialization: " << value.to_string() << std::endl;
}

void printer4(IsNumeric auto value) {
  std::cout << "SpecializationInt: " << value << std::endl;
}

template <typename T>
concept HasToString = requires(const T& value) {
  value.to_string();
};

void printer5(const auto& value) { std::cout << value << std::endl; }

void printer5(const HasToString auto& value) {
  std::cout << value.to_string() << std::endl;
}
