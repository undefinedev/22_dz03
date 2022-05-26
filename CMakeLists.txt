cmake_minimum_required(VERSION 3.22)
project(22_dz03)

set(CMAKE_CXX_STANDARD 23)

add_executable(22_dz03 main.cpp Library.cpp Library.hpp Book.cpp Book.hpp LibraryErrors.hpp LibraryVisitor.cpp LibraryVisitor.hpp)
