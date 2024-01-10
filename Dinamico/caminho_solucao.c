#include "bibliotecas.h"

//le e trata as informações do arquivo
void ler_dados(DADOS *dados, FILE *arquivo, POVOS *povos, int **matriz_adj, float *indice){

	int i;

	for(i=0;i<dados->P;i++){

		fscanf(arquivo,"%d",&povos->pesos[i]); //descartando
		fscanf(arquivo,"%d",&povos->pesos[i]);
		fscanf(arquivo,"%d",&povos->habilidade[i]);

		indice[i] = povos->saude[i] = povos->pesos[i]/povos->habilidade[i];

	}

	//função para ordenar o vetor saude
	qsort(povos->saude,dados->P,sizeof(float),comparador);

	int max = 0;
	int test;


//este laço recupera os indices dos povos ordenados, já que a função qsort esta implicita e esse dado foi perdido
	for(int i=0;i<dados->P;i++){
		for(int j=0;j<dados->P;j++){
			test = 0;
			for(int k=0;k<max;k++){
				if(j == indice[k]) test++;
			}
			if(indice[i]==povos->saude[j] && test==0){
				indice[i] = j;
				max++;
				break;
			}
		}
	}

	//aloca o espaço necessário para vetor
	i=0;
	int *vetor = (int *) malloc(sizeof(int)*(dados->P));

	while(i<dados->P){

		for(int j=0;j<dados->P;j++){
			if(indice[j]==i){
				vetor[i] = j;
			}
		}
		i++;
	}
	//vetor recupera os povos na ordem em que qsorte ordena os valores de razão peso/habilidade

	for(i=0;i<dados->P;i++) indice[i] = vetor[i]; //copia os valores para o vetor indice

	free(vetor); //libera o espaço alocado para vetor[]

	int p1,p2;

	//construindo a matriz de adjacencias
	for(i=0;i<dados->C;i++){

		fscanf(arquivo,"%d",&p1);
		fscanf(arquivo,"%d",&p2);

		fscanf(arquivo,"%d",&matriz_adj[p1-1][p2-1]);

		matriz_adj[p2-1][p1-1] = matriz_adj[p1-1][p2-1];
	}

}

void salvar_saida(FILE *arquivo, int *sol, int *S){ //salva o vetor solução no arquivo

	for(int i=0;i<*S;i++){
		fprintf(arquivo, "%d", sol[i]);
		if(i!=*S-1) fputc(32,arquivo); //printando espaço exceto no final da linha
	}
	char n = '\n';
	fputc(n,arquivo);
}
void inicializa_povos(POVOS *povos, int P){

	povos->saude = (float*) malloc(sizeof(float)*P);
	povos->pesos = (int *) malloc(sizeof(int)*P);
	povos->habilidade = (int *) malloc(sizeof(int)*P);
	
}

void calcula_solucao(DADOS *dados, int **matriz_adj, float *indice, int *sol, POVOS *povos, int *S){
	//dividir em varias funções.

	//aloca espaço necessário para vet
	int *vet = (int *) malloc(sizeof(int)*(dados->P));
	for(int i=0;i<dados->P;i++) vet[i] = -1; //inicializa todos os elementos com -1

	int v = 1; //contador para vetor
	int cont = 0;

	int pov; //guara o povo temporariamente
	int nave = 0; //guardara o peso que esta preenchendo a nave atualmente
	int hab = 0; //acumulara a habilidade
	int solg = 0; //contara o numero de soldados/guerreiros

	int j=0;

	pov = indice[0]; //pega o primeiro povo que é o mais eficiente neste caso

	vet[0] = indice[0]; //coloca o povo indice 0 no vetor de caminhos
	indice[0] = -1; //marca onde havia  o povo com -1 para mostrar que ele foi usado no caminho
	cont++; //conta um povo utilizado no caminho

	int aux;
	int D = 0;
	int teste=0;
	int i=0;

//montando um caminho viável da melhor maneira possível e que passa pelos povos com melhor saude peso/habilidade
	while(D<dados->D && cont<dados->P){

		aux = -2;
		for(i=0;i<dados->P;i++){
			if(indice[i]!=-1){
				aux = indice[i];

				if(matriz_adj[pov][aux]!=0){

					indice[i] = -1; //marca com -1 para não testá-lo novamente
					D += matriz_adj[pov][aux];
					if(D>dados->D){
						D -= matriz_adj[pov][aux];
						teste = 1;
						break;
					}
					pov = aux;
					vet[cont] = aux;
					cont++;

					i=0;
				}
			}
		}

		if(aux==-2 || teste == 1) break;
	}

	i=0;
	while(1){
		if(vet[i]==-1) break;
		i++;
	}

	//inicializa o vetor de solução todo com -1
	for(int j=0;j<(i*2+1);j++) sol[j] = -1; //inicializa todas as posições do vetor com -1

	int s = 1;
	j = 0;

	//percorre o caminho já criado preenchendo a nave com o máximo de soldados possível
	while(i>0){

		aux = vet[j];
		if(aux==-1) break;

		while(nave<=dados->W){
			nave = nave + povos->pesos[aux]; //acumula o peso atual na nave
			solg++; //conta quantos soldados estão sendo pegos
			hab = hab + povos->habilidade[aux]; //acumula o total de habilidade
		}


		//se exceder o peso total então retrocede uma etapa
		if(nave>dados->W){
			nave = nave - povos->pesos[aux];
			solg--;
			hab = hab - povos->habilidade[aux];
		}
		else{
			(*S) = (*S)+2;
			sol[s] = aux+1;
			s++;
			sol[s] = solg;
			s++;
			break;
		}

		(*S) = (*S)+2;
		sol[s] = aux+1;
		s++;
		sol[s] = solg;
		s++;
		j++;
		i--;

		solg = 0;
	}

	(*S)++;
	sol[0] = hab;
}

int comparador(const void *x, const void *y){ //um comparador utilizado na função qsort de ordenação
	return (*(int*)x - *(int*)y);
}
