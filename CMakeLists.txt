cmake_minimum_required(VERSION 3.0)

project(clownz80 LANGUAGES C)

add_library(clownz80-common STATIC
	"common.c"
	"common.h"
)

add_library(clownz80-interpreter STATIC
	"interpreter.c"
	"interpreter.h"
)

target_link_libraries(clownz80-interpreter PRIVATE clownz80-common)
