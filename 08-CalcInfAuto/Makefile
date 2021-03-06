# C Makefile using gcc, gdb and valgrind. 
# Modified version of Makefile using g++ & gdb by Roberto Nicolás Savinelli <rsavinelli@frba.utn.edu.ar>
# Tomás Agustín Sánchez <tosanchez@frba.utn.edu.ar>

CC = gcc
CFLAGS = -std=c18 -g3
INCLUDES = -I ./inc/
SOURCES = ./src/*.c
LEX 	  = flex -l
LEXSRC  = flex/*.l
LEXOUT = src/scanner.c
OUTPUT = Calculator.exe
LEAKS = leaks.log

all : compile debug leaks threads clean 
.PHONY: all

compile:
	$(LEX) -o $(LEXOUT) $(LEXSRC)
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT) && gdb -se $(OUTPUT)
	
leaks:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT) && valgrind --leak-check=yes --log-file="$(LEAKS)" --track-origins=yes ./$(OUTPUT)

clean:
	$(RM) ./$(OUTPUT) && $(RM) ./$(LOG)
