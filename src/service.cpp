#include <service/shopping_list_service.h>

#include <dto/serialization/item.h>
#include <dto/serialization/shopping_list.h>

#include <rest_utils.h>

#include <served/served.hpp>

int main(int, char **)
{
  served::multiplexer mux;
  shopping_list_service service;

  mux.handle("/shopping-list/add").get([&service](served::response &res, const served::request &req) {
    dto::item item {
      req.query["name"],
      std::atoi(req.query["amount"].c_str()), // FIXME: you can see the problem, can't you? :-)
      req.query["unit"]
    };

    service.add_item(item);

    to_http_response(std::string("ok"), res, "application/json");
  });

  mux.handle("/shopping-list/list").get([&service](served::response &res, const served::request &req) {
    to_http_response(service.get_list(), res, "application/json");
  });

  served::net::server server("0.0.0.0", "8080", mux);

  server.run(10);

  return 0;
}
