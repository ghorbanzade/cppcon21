#pragma once

#include <functional>
#include <iostream>

#include "cppcon/common.hpp"
#include "fmt/format.h"
#include "nlohmann/json.hpp"

struct MyDate {
  std::uint16_t year;
  std::uint16_t month;
  std::uint16_t day;

  std::string to_string() const;
  friend std::ostream& operator<<(std::ostream& os, const MyDate& dt);

  serialized_t serialize() const {
    std::cout << "serializing date" << std::endl;
    return serialized_t();
  }
};

void to_json(nlohmann::json& j, const MyDate& p);

template <>
struct fmt::formatter<MyDate> : fmt::formatter<std::string> {
  auto format(const MyDate& date, auto& ctx) {
    return formatter<std::string>::format(
        fmt::format("{}/{}/{}", date.month, date.day, date.year), ctx);
  }
};

template <>
struct std::hash<MyDate> {
  std::size_t operator()(const MyDate& date) const noexcept {
    return std::hash<std::string>{}(date.to_string());
  }
};
