#ifndef BIBLIOTECAS_H
#define BIBLIOTECAS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>

/*P = numero de povos, D = Distancia que zork pode andar
W = peso que a nave suporta e C = quantidade de caminhos*/

typedef struct TIPO_DADOS{
    int QTD_instancia, P, D, W, C;
}DADOS;

typedef struct POVOS{
    float *saude;
	int *pesos;
	int *habilidade;
}POVOS;

void salvar_saida(FILE *arquivo, int *sol, int *S);
void calcula_solucao(DADOS *dados, int **matriz_adj, float *indice, int *sol, POVOS *povos, int *S);
void ler_dados(DADOS *dados, FILE *arquivo, POVOS *povos, int **matriz_adj, float *indice);
void inicializa_povos(POVOS *povos, int P);
int comparador(const void *x, const void *y);
#endif