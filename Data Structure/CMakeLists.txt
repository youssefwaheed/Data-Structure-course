cmake_minimum_required(VERSION 3.23)
project(linked_list)

set(CMAKE_CXX_STANDARD 14)

add_executable(linked_list main.cpp "single linked list.h" "double linked list.h" stack.h)
