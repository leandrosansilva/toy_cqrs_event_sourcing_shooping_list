#include <dto/shopping_list.h>
#include <cereal/cereal.hpp>

namespace cereal {
  template <class Archive> inline
  void save(Archive &archive, const dto::shopping_list &list)
  {
    archive(cereal::make_nvp("items", list._items));
  }

  template <class Archive> inline
  void load(const Archive &archive, dto::shopping_list &list)
  {
    archive(cereal::make_nvp("items", list._items));
  }
}
