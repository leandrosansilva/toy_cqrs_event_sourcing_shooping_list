#pragma once

#include <event.h>
#include <event_repository.h>

struct event_publisher
{
  event_repository& _repository;

  event_publisher(event_repository& repository):
  _repository(repository)
  {
  }

  void publish(const events &e)
  {
    _repository._events.insert(
      _repository._events.end(), 
      e.begin(), 
      e.end()
    );
  }
};
