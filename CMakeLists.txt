cmake_minimum_required(VERSION 3.28)
project(cunoVM)

set(CMAKE_CXX_STANDARD 23)

add_executable(cunoVM main.cpp
        vm.cpp
        vm.h)
