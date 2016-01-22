#pragma once

#include <event.h>

namespace commands {

struct undo_event: event
{
  dto::shopping_list transform(const event_transformation_param &p) override
  {
    // FIXME: what if p.it is begin(events)?
    auto prev_event_iter = std::prev(p.it);

    if (auto ev = std::dynamic_pointer_cast<add_item_event>(*prev_event_iter)) {
      return remove_item_event(ev->_item).transform(p); 
    }

    if (auto ev = std::dynamic_pointer_cast<remove_item_event>(*prev_event_iter)) {
      return add_item_event(ev->_item).transform(p);
    }
   
    throw std::runtime_error("This action cannot be undone!?");
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
