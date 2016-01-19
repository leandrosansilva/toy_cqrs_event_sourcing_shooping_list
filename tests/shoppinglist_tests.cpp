#include <bandit/bandit.h>
#include <service/shopping_list_service.h>

using namespace bandit;

using sls = shopping_list_service;
using item_vector = std::vector<dto::item>;

go_bandit([]{
  describe("Test Shopping Service", []{
    it("List is empty", [&]{
      sls service;
      AssertThat(service.list_is_empty(), IsTrue());
    });

    it("Adds one item to the list makes the list not empty", [&]{
      sls service;
      service.add_item(dto::item{"item 1", 1, "kg"});
      AssertThat(service.list_is_empty(), IsFalse());
      auto list = service.get_list();
      AssertThat(list._items, EqualsContainer(std::vector<dto::item> {{"item 1", 1, "kg"}}));
    });

    it("Adds two different items results in a list with two items types", [&]{
      sls service;
      service.add_item(dto::item{"item 1", 1, "kg"});
      service.add_item(dto::item{"second item", 42, "mg"});

      auto list = service.get_list();
      AssertThat(
        list._items, 
        EqualsContainer(item_vector {
          {"item 1", 1, "kg"},
          {"second item", 42, "mg"},
        })
      );
    });

    it("Adds three items types, but aggregates two which are the same ", [&]{
      sls service;
      service.add_item(dto::item{"item 1", 1, "kg"});
      service.add_item(dto::item{"second item", 42, "mg"});
      service.add_item(dto::item{"item 1", 3, "kg"});

      auto list = service.get_list();
      AssertThat(
        list._items, 
        EqualsContainer(item_vector {
          {"item 1", 4, "kg"},
          {"second item", 42, "mg"},
        })
      );
    });


  });
});

int main(int argc, char **argv)
{
  return run(argc, argv);
}
