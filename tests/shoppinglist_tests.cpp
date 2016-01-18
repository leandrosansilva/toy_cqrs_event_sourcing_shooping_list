#include <bandit/bandit.h>
#include <service/shopping_list_service.h>

using namespace bandit;

go_bandit([]{
  describe("Test Shopping Service", []{
    shopping_list_service service;

    it("List is empty", [&]{
      AssertThat(service.list_is_empty(), IsTrue());
    });

    it("Adds one item to the list makes the list not empty", [&]{
      service.add_item(dto::item{"item 1", 1, "kg"});
      AssertThat(service.list_is_empty(), IsFalse());
    });
  });
});

int main(int argc, char **argv)
{
  return run(argc, argv);
}
