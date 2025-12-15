cmake_minimum_required(VERSION 3.0)

project(clownz80 LANGUAGES C)

add_library(clownz80 STATIC
	"z80.c"
	"z80.h"
)
