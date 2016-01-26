#pragma once

#include <dto/shopping_list.h>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

namespace cereal {
  template <typename Archive>
  inline void serialize(Archive &archive, const dto::shopping_list &list)
  {
    archive(cereal::make_nvp("items", list._items));
  }
}
