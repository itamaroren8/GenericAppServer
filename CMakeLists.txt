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

fetchcontent_declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG master
)

FetchContent_MakeAvailable(json)

add_executable(App main.cpp
        IDatabase.hpp
        SqliteDatabase.cpp
        SqliteDatabase.hpp
        Server.cpp
        Server.hpp
        Communicator.cpp
        Communicator.hpp
        CONSTANTS.hpp
        IRequestHandler.hpp
        LoginRequestHandler.cpp
        LoginRequestHandler.hpp
        Requests.hpp
        LoggedUser.hpp
        JsonDeserializer.cpp
        JsonDeserializer.hpp
        JsonSerializer.cpp
        JsonSerializer.hpp
        responses.hpp
        results.hpp
        Timer.h)

target_include_directories(App PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_libraries(App PRIVATE ${SQLite3_LIBRARIES})
target_include_directories(App PRIVATE ${sockpp_SOURCE_DIR}/include)
target_link_libraries(App PRIVATE Sockpp::sockpp)
target_link_libraries(App PRIVATE nlohmann_json::nlohmann_json)

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