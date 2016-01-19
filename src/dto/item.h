#pragma once

#include <string>

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
