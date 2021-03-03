cmake_minimum_required(VERSION 3.15)
project(playfair)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(files)
include_directories(output)

add_executable(playfair
        encodeAndDecode.c
        encodeAndDecode.h
        readAndWrite.c
        readAndWrite.h
        builder.c
        builder.h
        main.c)
