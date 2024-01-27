cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(3DCurvesTrivial)

set(CMAKE_CXX_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(
        CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} /JMC"
    )
else()
    set(
        CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-implicit-fallthrough"
    )
endif()

add_executable(
    3DCurvesTrivial
    main.cpp
    objects.h
)

install(
    TARGETS 3DCurvesTrivial
    DESTINATION bin
    EXPORT 3DCurvesTrivial
)

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT spreadsheet)