#include <iostream>
#include <string>
#include <vector>

#include "cppcon/concepts.hpp"
#include "cppcon/date.hpp"
#include "cppcon/print.hpp"
#include "cppcon/serialize.hpp"

template <>
struct serializer<MyDate> {
  serialized_t serialize(const MyDate& value) { return serialized_t(); }
};

int main() {
  MyDate date{.year = 2021, .month = 10, .day = 29};
  std::cout << date << std::endl;
  fmt::print("{}\n", date);
  std::cout << nlohmann::json(date).dump() << std::endl;

  print1("answer:");
  print1(42);
  print1(date);

  print2("answer:");
  print2(42);
  print2(date);

  printer1<std::string>().print("answer:");
  printer1<int>().print(42);
  printer1<MyDate>().print(date);

  printer2<std::string, std::string>().print("", "answer:");
  printer2<std::string, int>().print("", 42);
  printer2<std::string, MyDate>().print("", date);

  printer3<std::string>().print("answer:");
  printer3<int>().print(42);
  printer3<MyDate>().print(date);

  printer4("answer:");
  printer4(42);
  printer4(date);

  printer5("answer:");
  printer5(42);
  printer5(date);

  check("some-null", nullptr);
  check("some-boolean", true);
  check("some-number", 42.0f);
  check("some-string", "forty two");
  check("some-string", std::string("forty two"));
  check("some-array", std::vector<int>{42, 24, 54});

  check2("some-null", nullptr);
  check2("some-boolean", true);
  check2("some-number", 42.0f);
  check2("some-string", "forty two");
  check2("some-string", std::string("forty two"));
  check2("some-string", date.to_string());
  check2("some-array", std::vector<int>{42, 24, 54});
  check2("some-date", date);

  check("some-date", MyDate{2021, 10, 29});
  check("some-map",
        std::map<std::string, MyDate>{{"today", MyDate{2021, 10, 29}},
                                      {"yesterday", MyDate{2020, 10, 28}}});
}
