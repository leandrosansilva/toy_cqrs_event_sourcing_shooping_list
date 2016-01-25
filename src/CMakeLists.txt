# Empty

add_executable(server service.cpp)
target_link_libraries(server -lboost_system -lserved -lpthread -lre2)
