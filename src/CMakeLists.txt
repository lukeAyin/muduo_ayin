include_directories(../include)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
add_subdirectory(finger)
add_subdirectory(http)
add_subdirectory(echo)

