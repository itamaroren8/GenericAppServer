cmake_minimum_required(VERSION 4.2)
project(App)
find_package(SQLite3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        sockpp
        GIT_REPOSITORY https://github.com/fpagliughi/sockpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(sockpp)

add_executable(App main.cpp
        IDatabase.h
        SqliteDatabase.cpp
        SqliteDatabase.h
        Server.cpp
        Server.h
        Communicator.cpp
        Communicator.h
        CONSTANTS.h)

target_include_directories(App PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_libraries(App PRIVATE ${SQLite3_LIBRARIES})
target_include_directories(App PRIVATE ${sockpp_SOURCE_DIR}/include)
target_link_libraries(App PRIVATE Sockpp::sockpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(Threads REQUIRED)
    target_link_libraries(App PRIVATE Threads::Threads)
elseif(WIN32)
    add_custom_command(TARGET App POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:App>
            $<TARGET_FILE_DIR:App>
            COMMAND_EXPAND_LISTS
    )
endif()