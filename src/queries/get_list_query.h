#pragma once

#include <event_projector.h>
#include <dto/shopping_list.h>

namespace queries {

struct get_list_query
{
  const event_projector &_projector;

  get_list_query(const event_projector &projector):
  _projector(projector)
  {
  }

  dto::shopping_list run() const
  {
    return _projector.play();
  }
};

}
