#pragma once

#include <dto/shopping_list.h>
#include <dto/item.h>

#include <event_publisher.h>
#include <event_projector.h>

#include <commands/add_item_command.h>
#include <queries/empty_list_query.h>
#include <queries/get_list_query.h>

struct shopping_list_service
{
  event_repository _repository;
  event_publisher _publisher;
  event_projector _projector;

  shopping_list_service():
  _publisher(_repository),
  _projector(_repository)
  {
  }

  // FIXME: include timestamp
  void add_item(const dto::item &item)
  {
    auto events = commands::add_item_command(item).build_events();
    _publisher.publish(events);
  }

  dto::shopping_list get_list()
  {
    return queries::get_list_query(_projector).run();
  }

  bool list_is_empty()
  {
    return queries::empty_list_query(_projector).run();
  }
};
