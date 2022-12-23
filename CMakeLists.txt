cmake_minimum_required(VERSION 3.16)
project(bookstore_real)

set(CMAKE_CXX_STANDARD 14)

add_executable(bookstore_real main.cpp MyUll.h account.h program.h explain.h ErrorException.h book.h)
