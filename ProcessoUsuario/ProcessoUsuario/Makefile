#############################################################################
# Makefile for building: procUsuario
#############################################################################

CC = gcc
STD = -std=c99

HEADER = include/*.h
SOURCES = src/*.c
INCLUDE_GCH = include/*.gch

OUT = bin/procUsuario
DOXYGEN_CONFIG = docs/doxygen/doxygen_config

all:
	$(CC) $(STD) $(HEADER) $(SOURCES)
	mv a.out $(OUT)
	rm $(INCLUDE_GCH)

doxygen:

	doxygen  $(DOXYGEN_CONFIG)

