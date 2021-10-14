#include "cppcon/date.hpp"

#include <iostream>

#include "fmt/core.h"

std::string MyDate::to_string() const {
  return fmt::format("{}/{}/{}", month, day, year);
}

std::ostream& operator<<(std::ostream& o, const MyDate& date) {
  return o << date.year << '-' << date.month << '-' << date.day;
}

void to_json(nlohmann::json& j, const MyDate& p) {
  j = nlohmann::json{{"year", p.year}, {"month", p.month}, {"day", p.day}};
}

// void from_json(const nlohmann::json& j, MyDate& p) {
//   j.at("year").get_to(p.year);
//   j.at("month").get_to(p.month);
//   j.at("day").get_to(p.day);
// }
