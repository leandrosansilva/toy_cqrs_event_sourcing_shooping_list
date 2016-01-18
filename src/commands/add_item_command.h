#pragma once

#include <event.h>
#include <dto/item.h>

namespace commands {

struct add_item_event: event
{
  dto::item _item;

  add_item_event(const dto::item &item):
  _item(item)
  {
  }

  dto::shopping_list transform(const dto::shopping_list &list) override
  {
    return dto::shopping_list {std::vector<dto::item> {_item}};
  }
};

struct add_item_command
{
  dto::item _item;

  add_item_command(const dto::item &item):
  _item(item)
  {
  }

  events build_events()
  {
    return {
      std::make_shared<add_item_event>(_item)
    };
  }
};

}
