cmake_minimum_required(VERSION 3.10)
project(lexicon C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/main.c
    src/files.c
)

add_executable(lexicon ${SOURCES})
