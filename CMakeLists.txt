cmake_minimum_required(VERSION 3.10)

# Project name and version
project(EventDispatcher VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(event_dispatcher main.cpp event_dispatcher.cpp)

# Include directories
target_include_directories(event_dispatcher PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
