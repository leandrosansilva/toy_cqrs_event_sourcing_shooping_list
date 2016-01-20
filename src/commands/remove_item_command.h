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

  dto::shopping_list transform(const dto::shopping_list &list) override
  {
    auto copy_list = list;
    
    auto found(std::find_if(std::begin(copy_list._items), std::end(copy_list._items), 
      [this](const dto::item &item) {
        return item.name == _item.name;
      }
    ));

    if (found == std::end(copy_list._items)) {
      throw std::runtime_error("Item not found in the list!");
    }

    if (found->amount < _item.amount) {
      throw std::runtime_error("Insuficient items to remove!");
    }

    found->amount -= _item.amount;

    if (found->amount == 0) {
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
