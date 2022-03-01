include_directories(../../include)
add_executable(finger finger.cc)
find_library(muduo_net libmuduo_net.a
        HINTS ../../lib)
find_library(muduo_base libmuduo_base.a
        HINTS ../../lib)
target_link_libraries(finger ${muduo_net})
target_link_libraries(finger ${muduo_base})
target_link_libraries(finger pthread rt)