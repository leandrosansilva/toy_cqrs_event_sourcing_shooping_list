#include <service.h>

int main(int, char **)
{
  shopping_list_service shopping_service;
 
  rest_service service(shopping_service);

  served::net::server server("0.0.0.0", "8080", service.mux());

  server.run(10);

  return 0;
}
