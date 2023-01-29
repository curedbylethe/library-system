cmake_minimum_required(VERSION 3.24)
project(Library)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(Library
        main.cpp
        include/Database.h
        include/Database.cpp
        include/User.cpp
        include/User.h
        include/Library.cpp
        include/Library.h)