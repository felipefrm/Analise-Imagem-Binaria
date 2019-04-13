########## Makefile ############

all: main.o entradaSaida.o paradigma.o
	gcc entradaSaida.o paradigma.o main.o -o tp2

main.o: main.c entradaSaida.h paradigma.h
	gcc -g -c main.c
entradaSaida.o: entradaSaida.h entradaSaida.c
	gcc -g -c entradaSaida.c
paradigma.o: paradigma.h paradigma.c
	gcc -g -c paradigma.c
