#pragma once

#include <event.h>

namespace commands {

struct undo_event: event
{
  dto::shopping_list transform(const event_transformation_param &p) override
  {
    // FIXME: what if p.it is begin(events)?
    auto prev_event_iter = std::prev(p.it);

    if (auto ptr = std::dynamic_pointer_cast<add_item_event>(*prev_event_iter)) {
      return remove_item_event(ptr->_item).transform(p); 
    }
   
    return p.list;
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
