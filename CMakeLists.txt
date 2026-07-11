cmake_minimum_required(VERSION 3.13)

project(aether-lang)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Read version
file(READ "${CMAKE_SOURCE_DIR}/VERSION" AETHER_VERSION)
string(STRIP "${AETHER_VERSION}" AETHER_VERSION)

# Generate version header
configure_file(
    ${CMAKE_SOURCE_DIR}/src/version.hpp.in
    ${CMAKE_BINARY_DIR}/generated/version.hpp
)

# Source files
file(GLOB_RECURSE SOURCE_FILES
    src/*.cpp
    src/*.hpp
)

# Executable
add_executable(aether ${SOURCE_FILES}
    ${CMAKE_BINARY_DIR}/generated/version.hpp
)

# Include generated headers
target_include_directories(aether PRIVATE
    ${CMAKE_BINARY_DIR}/generated
)