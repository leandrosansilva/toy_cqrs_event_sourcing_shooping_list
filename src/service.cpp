#include <service/shopping_list_service.h>

#include <dto/serialization/item.h>
#include <dto/serialization/shopping_list.h>

#include <served/served.hpp>
#include <cereal/archives/json.hpp>
#include <sstream>

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
  });

  mux.handle("/shopping-list/list").get([&service](served::response &res, const served::request &req) {
    std::stringstream ss;
    cereal::JSONOutputArchive archive(ss);
    archive(service.get_list());
  });


  served::net::server server("0.0.0.0", "8080", mux);

  server.run(10);

  return 0;
}
