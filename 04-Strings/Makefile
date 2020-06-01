# C Makefile using gcc and gdb modified version of Makefile using g++ by Roberto Nicolas Savinelli <rsavinelli@est.frba.utn.edu.ar>
# Tomas Agustin Sanchez <tosanchez@est.frba.utn.edu.ar>

CC = gcc
CFLAGS = -std=c18 -Werror -Wall -pedantic-errors -Wextra -g3
INCLUDES = -I ./inc/
SOURCES = ./src/*.c


OUTPUT = test

.PHONY: compile debug clean vg

compile:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT) && gdb -se $(OUTPUT)
vg:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT) && valgrind --leak-check=yes --log-file="leaks.log" --track-origins=yes ./$(OUTPUT)

clean:
	$(RM) ./$(OUTPUT)
