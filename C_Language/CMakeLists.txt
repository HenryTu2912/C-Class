cmake_minimum_required(VERSION 3.24)
project(C_Language C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Language bitmap/bitmap.h bitmap/bitmap.c bitmap/App.c)
