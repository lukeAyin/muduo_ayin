include_directories(../include)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
#add_subdirectory(finger)
#add_subdirectory(DBConnector)
add_subdirectory(http)
set(AYIN_SRC
        echo.cc
        )
add_executable(echo ${AYIN_SRC})
find_library(muduo_net libmuduo_net.a
    HINTS ../lib/lib)
#set(muduo_net ../lib/lib/libmuduo_net.a)
find_library(muduo_base libmuduo_base.a
    HINTS ../lib/lib)
#set(muduo_base ../lib/lib/libmuduo_base.a)
message(${muduo_net} " is muduo_net path!")
message(${muduo_base} " is muduo_base path!")
target_link_libraries(echo ${muduo_net})
target_link_libraries(echo ${muduo_base})
# target_link_libraries(echo /home/ayin/Documents/muduo_ayin/lib/libmuduo_net.a)
# target_link_libraries(echo /home/ayin/Documents/muduo_ayin/lib/libmuduo_base.a)
target_link_libraries(echo pthread rt)
