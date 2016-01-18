#pragma once

#include <event_projector.h>
#include <dto/shopping_list.h>

namespace queries {

struct empty_list_query
{
  const event_projector &_projector;

  empty_list_query(const event_projector &projector):
  _projector(projector)
  {
  }

  bool run() const
  {
    dto::shopping_list list = _projector.play();
    return list._items.empty();
  }
};

}
