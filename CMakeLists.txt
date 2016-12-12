cmake_minimum_required(VERSION 3.5.1)
project(eXiaSaver)

set(CMAKE_CXX_STANDARD 11)

add_executable(eXiaSaver src/launcher.c)
add_executable(eXiaSaver1 src/static.c)
add_executable(eXiaSaver2 src/dynamic.c)
