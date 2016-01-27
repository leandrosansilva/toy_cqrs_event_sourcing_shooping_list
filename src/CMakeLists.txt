# Empty

add_executable(main main.cpp)
target_link_libraries(main -lboost_system -lserved -lpthread -lre2)
cotire(main)
add_dependencies(main served)
