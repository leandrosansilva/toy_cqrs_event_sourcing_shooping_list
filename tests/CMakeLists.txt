add_executable(shopping_tests shoppinglist_tests.cpp)
cotire(shopping_tests)
add_test(ShoppingTests shopping_tests)
