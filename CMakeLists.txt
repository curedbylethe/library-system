cmake_minimum_required(VERSION 3.24)
project(Library)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)

# Add include directory to include path
include_directories(include)

# Add main.cpp and include/Database.h to the executable
add_executable(Library
        main.cpp
        include/Database.h
        include/Database.cpp)