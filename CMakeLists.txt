cmake_minimum_required(VERSION 3.14)
project(keyvaluestore C)

set(CMAKE_C_STANDARD 99)

#set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS_RELEASE "-march=native -O2 -DNDEBUG")

add_executable(keyvaluestore main.c src/terms.c include/terms.h src/hashmap.c include/hashmap.h src/hyperedges.c include/hyperedges.h)