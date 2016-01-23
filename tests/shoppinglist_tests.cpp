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

    it("Adds two different items in reverse order results in a list with two items types", [&]{
      sls service;
      service.add_item(dto::item{"second item", 42, "mg"});
      service.add_item(dto::item{"item 1", 1, "kg"});

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

    it("Adds two items of two types, but then remove the first one", [&]{
      sls service;
      service.add_item(dto::item{"item 1", 1, "kg"});
      service.add_item(dto::item{"item 2", 1, "mg"});
      service.remove_item(dto::item{"item 1", 1, "kg"});

      auto list = service.get_list();
      AssertThat(
        list._items, 
        EqualsContainer(item_vector {
          {"item 2", 1, "mg"}
        })
      );
    });

    it("Adds several items of two types, but then remove some of the first one", [&]{
      sls service;
      service.add_item(dto::item{"item 1", 5, "kg"});
      service.add_item(dto::item{"item 2", 43, "mg"});
      service.add_item(dto::item{"item 1", 7, "kg"});
      service.remove_item(dto::item{"item 1", 4, "kg"});

      auto list = service.get_list();
      AssertThat(
        list._items, 
        EqualsContainer(item_vector {
          {"item 1", 8, "kg"},
          {"item 2", 43, "mg"}
        })
      );
    });

    it("Adds two items of different types and undo the last added one", [&]{
      sls service;
      service.add_item(dto::item{"item 1", 5, "kg"});
      service.add_item(dto::item{"item 2", 43, "mg"});
      service.undo_last_action();

      auto list = service.get_list();
      AssertThat(
        list._items, 
        EqualsContainer(item_vector {
          {"item 1", 5, "kg"}
        })
      );
    });

    it("Adds three items, remove the first one and then undo this removal and the last addition", [&]{
      sls service;
      service.add_item(dto::item{"third item", 35, "km"});
      service.add_item(dto::item{"item 1", 5, "kg"});
      service.add_item(dto::item{"item 2", 43, "mg"});
      service.remove_item(dto::item{"item 1", 4, "kg"});
      service.add_item(dto::item{"third item", 3, "km"});
      service.undo_last_action();
      service.undo_last_action();

      auto list = service.get_list();
      AssertThat(
        list._items, 
        EqualsContainer(item_vector {
          {"item 1", 5, "kg"},
          {"item 2", 43, "mg"},
          {"third item", 35, "km"}
        })
      );
    });


  });
});

int main(int argc, char **argv)
{
  return run(argc, argv);
}
