# C Makefile using gcc, gdb and valgrind. 
# Modified version of Makefile using g++ & gdb by Roberto Nicolas Savinelli <rsavinelli@est.frba.utn.edu.ar>
# Tomas Agustin Sanchez <tosanchez@est.frba.utn.edu.ar>

CC = gcc
CFLAGS = -std=c18 -Werror -Wall -pedantic-errors -Wextra -g3
INCLUDES = -I ./inc/
SOURCES = ./src/*.c

OUTPUT = test.exe
LEAKS = leaks.log
HELGRIND = threads.log

all : compile debug leaks threads clean 
.PHONY: all

compile:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT) && gdb -se $(OUTPUT)
	
leaks:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT) && valgrind --leak-check=yes --log-file="$(LEAKS)" --track-origins=yes ./$(OUTPUT)

threads:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT) && valgrind --tool=helgrind --log-file="$(HELGRIND)" ./$(OUTPUT)

clean:
	$(RM) ./$(OUTPUT) && $(RM) ./$(LOG)
