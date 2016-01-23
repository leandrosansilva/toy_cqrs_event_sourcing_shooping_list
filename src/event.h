#pragma once

#include <vector>
#include <memory>

#include <dto/shopping_list.h>

struct event;

using event_ptr = std::shared_ptr<event>;
using events = std::vector<event_ptr>;

struct event_transformation_param
{
  const dto::shopping_list &list;
  const events &all_events;
  const events::const_iterator &it;
};

struct event
{
  virtual dto::shopping_list transform(const event_transformation_param &) = 0;
};
