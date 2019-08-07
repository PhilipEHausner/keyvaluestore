cmake_minimum_required(VERSION 3.14)
project(keyvaluestore C)

set(CMAKE_C_STANDARD 99)

add_executable(keyvaluestore main.c src/terms.c include/terms.h src/hashmap.c include/hashmap.h)