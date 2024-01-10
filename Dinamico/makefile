all: tp2 limpar

tp2: main.o caminho_solucao.o
	gcc main.o caminho_solucao.o -o tp2 -lm

main.o: main.c bibliotecas.h
	gcc -c main.c -o main.o

solucao_comp.o: caminho_solucao.c bibliotecas.h
	gcc -c caminho_solucao.c -o caminho_solucao.o

limpar:
	rm -rf *.o *~ printy
