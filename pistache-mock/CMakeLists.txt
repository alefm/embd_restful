cmake_minimum_required(VERSION 2.6)

project(pistache-mock)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
# set(CMAKE_CXX_STANDARD 11)

link_directories($ENV{LD_LIBRARY_PATH})

include_directories( app/include/ )

file(GLOB headers "app/include/**/*.hpp")
file(GLOB sources "app/src/**/*.cpp")

# Set MacOsx include and lib directories
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/app/include"
        "/usr/local/include"
    )

    link_directories(/usr/local/lib)
    set(CMAKE_MACOSX_RPATH ON)
endif()

# link_directories("/usr/local/lib")

add_executable(pistache-mock "app/src/main.cpp" ${sources} ${headers})
target_link_libraries(pistache-mock pistache jansson sqlite3)

install(TARGETS pistache-mock
    RUNTIME DESTINATION bin
    DESTINATION ${CMAKE_INSTALL_BINDIR})