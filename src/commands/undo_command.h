#pragma once

#include <event.h>

namespace commands {

struct undo_event: event
{
  dto::shopping_list transform(const event_transformation_param &p) override
  {
    return undo(p, 1);
  }

  dto::shopping_list undo(const event_transformation_param &p, int undone_action_distance)
  {
    if (std::distance(std::begin(p.all_events), p.it) < undone_action_distance) {
      return p.list;
    }

    auto prev_event_iter = std::prev(p.it, undone_action_distance);

    if (auto ev = std::dynamic_pointer_cast<add_item_event>(*prev_event_iter)) {
      return remove_item_event(ev->_item).transform(p);
    }

    if (auto ev = std::dynamic_pointer_cast<remove_item_event>(*prev_event_iter)) {
      return add_item_event(ev->_item).transform(p);
    }

    if (auto ev = std::dynamic_pointer_cast<undo_event>(*prev_event_iter)) {
      event_transformation_param prev_p {
        p.list,
        p.all_events,
        prev_event_iter
      };

      return undo(prev_p, undone_action_distance + 1);
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
