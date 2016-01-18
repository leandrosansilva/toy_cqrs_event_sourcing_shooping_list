#pragma once

#include <vector>
#include <memory>

#include <dto/shopping_list.h>

struct event;

using event_ptr = std::shared_ptr<event>;
using events = std::vector<event_ptr>;

struct event
{
  virtual dto::shopping_list transform(const dto::shopping_list &) = 0;
};
