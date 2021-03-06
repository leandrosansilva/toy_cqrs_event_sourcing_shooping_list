#pragma once

#include <string>
#include <ostream>

namespace dto {

struct item
{
  std::string name;
  int amount;
  std::string unit;
};

}

bool operator==(const dto::item &a, const dto::item &b)
{
  return a.name == b.name 
         && a.amount == b.amount 
         && a.unit == b.unit;
}

namespace std {
std::ostream &operator<<(std::ostream &os, const dto::item &item)
{
  return os << "dto::item<\"" 
     << item.name << "\", "
     << item.amount << ", \""
     << item.unit << "\">";
}
}
