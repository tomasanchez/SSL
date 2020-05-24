# C Makefile using gcc and gdb
# Tomas Agustin Sanchez <tosanchez@est.frba.utn.edu.ar>

CC = gcc
CFLAGS = -std=c18 -Werror -Wall -pedantic-errors -Wextra
INCLUDES = -I ./inc/
SOURCES = ./src/*.c


OUTPUT = test

.PHONY: compile debug clean

compile:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -g3 -o $(OUTPUT) && gdb -se $(OUTPUT)

clean:
	$(RM) ./$(OUTPUT)