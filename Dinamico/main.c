#include "bibliotecas.h"

int main(){
	
	//funçoes para medir o tempo
	struct rusage r_usage; //Faz parte da função Getrusage

	//gettime of day
	struct timeval tv0,tv1;
	double tempo_final, tempo_inicial, time;
    gettimeofday(&tv0, NULL);
    //gettime of day
	
	int i;
	DADOS dados;
	POVOS povos;

	int **matriz_adj;
	float *indice;
	int *solucao;
	int num_solucao=0; //indice do vetor solução

	FILE *arquivo = fopen("entrada.txt", "r"); // abre o arquivo de entrada
	FILE *arq_saida = fopen("saida.txt","a+"); //abre o arquivo para gravação de dados de saida

	if(arquivo == NULL){
		printf("Erro ao abrir arquivo!\n");
		return 0;
	}
	
	if(arq_saida == NULL){
		printf("Erro ao abrir arquivo!\n");
		return 0;
	}

	fscanf(arquivo,"%d",&dados.QTD_instancia);



	for(i=0;i<dados.QTD_instancia;i++){

		printf("_________________________\nInstancia %d\n_________________________\n",i+1);

		fscanf(arquivo,"%d",&dados.P);
		fscanf(arquivo,"%d",&dados.D);
		fscanf(arquivo,"%d",&dados.W);
		fscanf(arquivo,"%d",&dados.C);

		//aloca a matriz dinamicamente e inicia com zeros
		matriz_adj = (int **) calloc(dados.P,sizeof(int*));

		for(int j=0;j<dados.P;j++){
			matriz_adj[j] = (int *) calloc(dados.P,sizeof(int));
		}

		//alocando espaço para todos as variaveis que vão ser usadas
		inicializa_povos(&povos, dados.P);
		indice = (float*) malloc(sizeof(float)*dados.P);
		solucao = (int *) malloc(sizeof(int)*(dados.P*2+1));

		//lendo e tratando todos os dados de entrada
		ler_dados(&dados,arquivo,&povos,matriz_adj,indice);

		printf("\nPeso/Habilidade\n");
		for(int j=0;j<dados.P;j++){
			printf("Povo %d: %d %d\n",j+1,povos.pesos[j],povos.habilidade[j]);
		}
		printf("\n");

		//função que retorna o vetor solução
		calcula_solucao(&dados, matriz_adj, indice, solucao, &povos, &num_solucao);

		printf("Povos: %d\n",dados.P);
		printf("Distancia máxima: %d\n",dados.D);
		printf("Peso máximo suportado: %d\n",dados.W);
		printf("Qtd. caminhos: %d\n",dados.C);

		printf("\nSolucao:\n");
		for(int j=0;j<num_solucao;j++) printf("%d ",solucao[j]);
		printf("\n");

		//salva o vetor solução no arquivo
		salvar_saida(arq_saida,solucao,&num_solucao);

		num_solucao = 0; //importante zerar para a próxima instancia

		for(int j=0;j<dados.P;j++){
			free(matriz_adj[j]);
		}

		//liberando o espaço alocado
		free(matriz_adj);
		free(indice);
		free(povos.saude);
		free(povos.pesos);
		free(povos.habilidade);

	}


	gettimeofday(&tv1, NULL);
	tempo_final = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
	tempo_inicial = (double)(tv0.tv_sec) + (double)(tv0.tv_usec)/ 1000000.00;
	time = (tempo_final - tempo_inicial);
	printf("Gettimeofday: (%f)\n",time);
	int minutos, segundos;
	minutos = time/60;
	segundos = (int) time%60; 
	//convertendo o tempo que e doouble para inteiro
	printf(" %d min %d seg\n",minutos,segundos);

	//Getrusage
	getrusage(RUSAGE_SELF,&r_usage);
	printf("CPU usage: User = %ld.%06ld,System = %ld.%06ld\n",r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec,r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);
	//Getrusage
	fclose(arquivo);
	fclose(arq_saida);
	return 0;

}