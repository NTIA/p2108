# TODO confirm min version with testing
cmake_minimum_required(VERSION 3.7...3.29)

# The line above doesn't work for CMake<3.12; handle those cases:
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Set the project name and metadata
project(
    ITS.ITU.PSeries.P2108
    VERSION 1.0
    DESCRIPTION "Recommendation ITU-R P.2108, U.S. Reference Implementation"  # CMake 3.9+
    LANGUAGES CXX
)

# Project-wide settings/variables
set(P2108_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}")

# The library code and CMakeLists.txt are in ./src/
add_subdirectory(src)
