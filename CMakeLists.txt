cmake_minimum_required(VERSION 3.16)
project(ERMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find nlohmann_json package
find_package(nlohmann_json 3.9.1 REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/ERMS.cpp
    src/main.cpp
    src/Storage.cpp
    src/Stats.cpp
)

# Create executable
add_executable(erms ${SOURCES})

# Link nlohmann_json
target_link_libraries(erms PRIVATE nlohmann_json::nlohmann_json)
