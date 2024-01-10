#ifndef BIBLIOTECAS_H
#define BIBLIOTECAS_H

//este arquivo contém as bilbiotecas necessárias para o funcionamento das funções utilizadas no programa

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>

typedef struct DADOS{
    int P,D,W,C;
    int **matriz;
    float *vet_peso,*vet_hab;
}DADOS;

void imprime(FILE *arquivo_output, int *result, int *s);
int *caminhos(int *pov_position,  int *S,DADOS *info);
int *ordenacao(float *vet, int *P);
void leitura(FILE *arquivo_input,DADOS *info);
float *peso(float *peso, float *hab, int *P);


#endif