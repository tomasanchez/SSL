# C Makefile using gcc, gdb and valgrind. 
# Modified version of Makefile using g++ & gdb by Roberto Nicolás Savinelli <rsavinelli@frba.utn.edu.ar>
# Tomás Agustín Sánchez <tosanchez@frba.utn.edu.ar>

CC = gcc
CFLAGS = -std=c18 -g3
INCLUDES = -I ./inc/
SOURCES = ./src/*.c
YACCC  	= bison -v
YACCTAB = inc/token_tab.h
YACCOUT = src/parser.c
YACC	= bison/parser.y
LEXC 	= flex -l
LEX  	= bison/scanner.l
LOUT 	= src/scanner.c
OUTPUT 	= Calculator.exe
LEAKS 	= leaks.log

all : compile debug leaks threads clean 
.PHONY: all

compile:
	$(YACCC) --defines=$(YACCTAB) --output=$(YACCOUT) $(YACC)
	$(LEXC) -o $(LOUT) $(LEX)
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT)

debug:
	make compile && gdb -se $(OUTPUT)
	
leaks:
	make compile && valgrind --leak-check=yes --log-file="$(LEAKS)" --track-origins=yes ./$(OUTPUT)

clean:
	$(RM) ./$(OUTPUT) && $(RM) ./$(LOG)
