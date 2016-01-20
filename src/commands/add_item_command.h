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
    auto list_copy = list;
    
    auto found = std::find_if(std::begin(list_copy._items), std::end(list_copy._items), 
      [this] (const dto::item &item) {
        return item.name == _item.name
               && item.unit == _item.unit;
      }
    );
    
    if (found != std::end(list_copy._items)) {
      found->amount += _item.amount;
      return list_copy;
    }
    
    list_copy._items.push_back(_item);
    return list_copy;
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
