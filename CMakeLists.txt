cmake_minimum_required(VERSION 4.2)
project(App)
find_package(SQLite3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(App main.cpp
        IDatabase.h
        SqliteDatabase.cpp
        SqliteDatabase.h
        Server.cpp
        Server.h)

target_include_directories(App PRIVATE ${SQLite3_LIBRARIES})
target_link_libraries(App PRIVATE ${SQLite3_LIBRARIES})