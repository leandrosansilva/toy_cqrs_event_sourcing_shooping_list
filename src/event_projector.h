#pragma once

#include <algorithm>

#include <event_repository.h>

struct event_projector
{
  event_repository& _repository;

  event_projector(event_repository &repository):
  _repository(repository)
  {
  }

  dto::shopping_list play() const
  {
    return std::accumulate(
      std::begin(_repository._events), 
      std::end(_repository._events),
      dto::shopping_list(),
      [](const dto::shopping_list &list, event_ptr ev) {
        return ev->transform(list);
      }
    );
  }
};
