add_executable(test_parser http_parser_test.cpp)
find_library(muduo_net libmuduo_net.a
        HINTS ../../lib)
find_library(muduo_base libmuduo_base.a
        HINTS ../../lib)
target_link_libraries(test_parser ${muduo_net})
target_link_libraries(test_parser ${muduo_base})
target_link_libraries(test_parser pthread rt)