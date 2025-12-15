cmake_minimum_required(VERSION 3.0)

project(clownz80 LANGUAGES C)

add_library(clownz80-common STATIC
	"common.c"
	"common.h"
)

add_library(clownz80 STATIC
	"clownz80.c"
	"clownz80.h"
)

target_link_libraries(clownz80 PRIVATE clownz80-common)
