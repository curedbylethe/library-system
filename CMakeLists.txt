cmake_minimum_required(VERSION 3.24)
project(Library)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(Library
        main.cpp
        src/Database.cpp
        src/User.cpp
        include/Library.cpp
        include/Library.h
        src/Book.cpp)