# Instrução para compilar o programa

all: programa clean

programa: main.o funcoes.o
	gcc main.o funcoes.o -o tp2 -lm

main.o: main.c bibliotecas.h
	gcc -c main.c -o main.o

funcoes.o: funcoes.c bibliotecas.h
	gcc -c funcoes.c -o funcoes.o

clean:
	rm -rf *.o *~ printy
