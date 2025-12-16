cmake_minimum_required(VERSION 3.0...3.10)

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

add_library(clownz80-disassembler STATIC
	"disassembler.c"
	"disassembler.h"
)

target_link_libraries(clownz80-disassembler PRIVATE clownz80-common)

add_executable(clownz80-disassembler-test
	"disassembler-test.c"
)

target_link_libraries(clownz80-disassembler-test PRIVATE clownz80-disassembler)
