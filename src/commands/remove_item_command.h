#pragma once

#include <event.h>
#include <dto/item.h>
#include <stdexcept>

namespace commands {

struct remove_item_event: event
{
  dto::item _item;

  remove_item_event(const dto::item &item):
  _item(item)
  {
  }

  dto::shopping_list transform(const event_transformation_param &p) override
  {
    auto copy_list = p.list;

    auto found(std::find_if(std::begin(copy_list._items), std::end(copy_list._items),
      [this](const dto::item &item) {
        return item.name == _item.name;
      }
    ));

    if (found == std::end(copy_list._items) || found->amount < _item.amount) {
      return copy_list;
    }

    if ((found->amount -= _item.amount) == 0) {
      copy_list._items.erase(found);
    }

    return copy_list;
  }
};

struct remove_item_command
{
  dto::item _item;

  remove_item_command(const dto::item &item):
  _item(item)
  {
  }

  events build_events()
  {
    return {
      std::make_shared<remove_item_event>(_item)
    };
  }
};

}
