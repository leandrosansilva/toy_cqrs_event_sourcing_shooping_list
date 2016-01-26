#pragma once

#include <dto/item.h>
#include <cereal/cereal.hpp>

namespace cereal {
  template <class Archive>
  inline void serialize(Archive &archive, const dto::item &item)
  {
    archive(
      cereal::make_nvp("name", item.name),
      cereal::make_nvp("amount", item.amount),
      cereal::make_nvp("unit", item.unit)
    );
  }
}
