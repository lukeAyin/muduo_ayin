#include_directories(../../include)
#add_executable(DBConnection DBConnector.cpp)
#find_library(muduo_net libmuduo_net.a
#        HINTS ../../lib)
#find_library(muduo_base libmuduo_base.a
#        HINTS ../../lib)
#target_link_libraries(DBConnection ${muduo_net})
#target_link_libraries(DBConnection ${muduo_base})
#target_link_libraries(DBConnection pthread rt)
add_subdirectory(test)
