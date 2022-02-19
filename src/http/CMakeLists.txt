include_directories(../../include)
add_subdirectory(test)
add_executable(http_server main.cpp)
find_library(muduo_net libmuduo_net.a
        HINTS ../../lib)
find_library(muduo_base libmuduo_base.a
        HINTS ../../lib)
set(http_SRCS
        http_server.cpp
        http_parser.cpp
        io_file.cpp
        http_response.cpp)
file(MAKE_DIRECTORY static)
file(COPY ./static/ DESTINATION static)
add_library(muduo_http ${http_SRCS})
target_link_libraries(http_server ${muduo_net})
target_link_libraries(http_server ${muduo_base})
target_link_libraries(http_server pthread rt)
target_link_libraries(http_server muduo_http)