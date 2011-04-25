AM_CFLAGS=-Wall -ggdb

BUILT_SOURCES=parser_bison.h
AM_YFLAGS=-d --debug
AM_LFLAGS=-o${LEX_OUTPUT_ROOT}.c

bin_PROGRAMS= orionemu

orionemu_SOURCES= 	main.c \
			parser_ast.c \
			parser_flex.l \
			parser_bison.y