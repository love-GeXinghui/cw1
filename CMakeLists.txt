cmake_minimum_required(VERSION 3.17)
project(cw1 C)

set(CMAKE_C_STANDARD 99)

add_executable(cw1 book_mangement.h users.h main.c book_mangement.c users.c)