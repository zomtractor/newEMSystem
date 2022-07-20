cmake_minimum_required(VERSION 3.20)
project(newEMSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(newEMSystem src/main.cpp src/List.hpp src/Array.hpp src/HashSet.hpp src/Employee.cpp src/Employee.h src/EMSystem.cpp src/EMSystem.h src/EasyDate.cpp src/EasyDate.h)
