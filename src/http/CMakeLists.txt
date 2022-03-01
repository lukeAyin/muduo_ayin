include_directories(../include)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
find_library(muduo_net libmuduo_net.a
        HINTS ../lib/lib)
#set(muduo_net ../lib/lib/libmuduo_net.a)
find_library(muduo_base libmuduo_base.a
        HINTS ../lib/lib)
set(http_src main.cpp
            http_conn.cpp
        http_type.cpp
        http_decoder.cpp http_server.cpp)
add_executable(http ${http_src})
target_link_libraries(http ${muduo_base})
target_link_libraries(http ${muduo_net})