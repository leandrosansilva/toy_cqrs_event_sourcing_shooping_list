#pragma once

#include <served/served.hpp>
#include <cereal/archives/json.hpp>
#include <sstream>
#include <string>

template<typename T>
inline void to_http_response(const T &t, served::response &res, const std::string &mime_type)
{
  res.set_header("Content-Type", mime_type);

  res << ([&] {
    std::ostringstream ss; 
    {
      cereal::JSONOutputArchive archive(ss);
      archive(cereal::make_nvp("result", t));
    }
    return ss.str();
  })();
}
