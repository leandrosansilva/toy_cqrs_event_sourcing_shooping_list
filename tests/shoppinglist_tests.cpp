#include <bandit/bandit.h>
#include <algorithm>

using namespace bandit;

go_bandit([]{
  describe("Booleans", []{
    it("True should be true", []{
      AssertThat(true, IsTrue());
    });
  });
});

int main(int argc, char **argv)
{
  return run(argc, argv);
}
