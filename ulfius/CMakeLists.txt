cmake_minimum_required(VERSION 2.6)

project(ulfius_mock)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

link_directories($ENV{LD_LIBRARY_PATH})

include_directories( app/include/ )

file(GLOB headers "app/include/**/*.h" )
file(GLOB sources "app/src/**/*.c" )

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

add_executable(ulfius_mock "app/src/main.c" ${sources} ${headers})
target_link_libraries(ulfius_mock ulfius jansson orcania yder sqlite3)

install(TARGETS ulfius_mock
    RUNTIME DESTINATION bin
    DESTINATION ${CMAKE_INSTALL_BINDIR})