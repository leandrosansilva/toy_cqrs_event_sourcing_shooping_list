#pragma once

#include <algorithm>

#include <event_repository.h>

struct event_projector
{
  struct accumulator
  {
    events::iterator it;
    dto::shopping_list list;
  };

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
      accumulator{std::begin(_repository._events), {}},
      [this](const accumulator &acc, event_ptr ev) {
        event_transformation_param param {
          acc.list,
          _repository._events,
          acc.it
        };

        return accumulator {
          std::next(acc.it),
          ev->transform(param)
        };
      }
    ).list;
  }
};
