#pragma once

#include <event.h>

namespace commands {

struct undo_event: event
{
  dto::shopping_list transform(const dto::shopping_list &list) override
  {
    return list;
  }
};

struct undo_command
{
  events build_events()
  {
    return {
      std::make_shared<undo_event>()
    };
  }
};

}
