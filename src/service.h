#pragma once

#include <dto/serialization/item.h>
#include <dto/serialization/shopping_list.h>

#include <rest_utils.h>
#include <served/served.hpp>
#include <service/shopping_list_service.h>

dto::item build_item(const served::request &req)
{
  dto::item item {
    req.query["name"],
    std::atoi(req.query["amount"].c_str()), // FIXME: you can see the problem, can't you? :-)
    req.query["unit"]
  };

  return item;
}

struct rest_service
{
  served::multiplexer _mux;

  served::multiplexer &mux()
  {
    return _mux;
  }

  rest_service(shopping_list_service &service)
  {
    _mux.handle("/shopping-list/add").get([&service](served::response &res, const served::request &req) {
      service.add_item(build_item(req));
      to_http_response(std::string("ok"), res, "application/json");
    });

    _mux.handle("/shopping-list/list").get([&service](served::response &res, const served::request &) {
      to_http_response(service.get_list(), res, "application/json");
    });

    _mux.handle("/shopping-list/undo").get([&service](served::response &res, const served::request &) {
      service.undo_last_action();
      to_http_response(std::string("ok"), res, "application/json");
    });
  }
};
