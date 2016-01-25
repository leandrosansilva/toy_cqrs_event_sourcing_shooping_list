#include <served/served.hpp>

int main(int, char **)
{
  served::multiplexer mux;

  served::net::server server("0.0.0.0", "8080", mux);

  server.run(10);

  return 0;
}
