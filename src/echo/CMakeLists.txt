find_library(muduo_net libmuduo_net.a
        HINTS ../lib)
find_library(muduo_base libmuduo_base.a
        HINTS ../lib)
message(${muduo_net} " is muduo_net path!")
message(${muduo_base} " is muduo_base path!")
add_executable(echo echo.cc)
target_link_libraries(echo ${muduo_net})
target_link_libraries(echo ${muduo_base})
# target_link_libraries(echo /home/ayin/Documents/muduo_ayin/lib/libmuduo_net.a)
# target_link_libraries(echo /home/ayin/Documents/muduo_ayin/lib/libmuduo_base.a)
target_link_libraries(echo pthread rt)