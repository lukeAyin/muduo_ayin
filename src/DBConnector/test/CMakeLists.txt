#add_executable(SQLtest mysql_c_test.cpp)
add_executable(SQLtest mysql_cpp_test.cpp)
find_library(mysqlclient NAMES mysqlclient)
message(${mysqlclient} "ayin")
find_library(mysqlpp NAMES mysqlpp)
message(${mysqlpp} )
#target_link_libraries(SQLtest ${mysqlclient})
#find_library(maria NAMES mariadb)
#message(${maria})
target_link_libraries(SQLtest ${mysqlpp})
#target_link_libraries(SQLtest ${maria})
set(
        CMAKE_CXX_FLAGS
        "-I/usr/include/mysql"
        #"-lmysqlclient"
)
