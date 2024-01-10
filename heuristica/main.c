#include "bibliotecas.h"

//Função principal
int main(){ 
	struct rusage r_usage; //Faz parte da função Getrusage

	//gettime of day
	struct timeval tv0,tv1;
	double tempo_final, tempo_inicial, time;
    gettimeofday(&tv0, NULL);
    //gettime of day

	int opt;

	// Getopt(&opt, &argc, argv, &name_file_input, &name_file_output);

	FILE *arquivo_input,*arquivo_output;
	arquivo_input = fopen("entrada.txt","rt");

//testa se arquivo não foi encontrado
	if(arquivo_input==NULL){ 
		
		printf("Arquivo nao encontrado\n");
		return 0;
	}
	
	DADOS info;
	int instancia,P,D,W,C;

///// teste
	fscanf(arquivo_input,"%d",&instancia);
///// teste

	float *prop;
	int *pov_position;
	arquivo_output = fopen("saida.txt","a+");

	for(int i=0;i<instancia;i++){

		fscanf(arquivo_input,"%d",&P);
		fscanf(arquivo_input,"%d",&D);
		fscanf(arquivo_input,"%d",&W);
		fscanf(arquivo_input,"%d",&C);

		printf("descricao %d , \n Povo: %d ,\n Distancia: %d ,\n Peso W: %d ,\n Caminhos: %d\n\n",i+1,P,D,P,W);//teste

		info.matriz = (int**) calloc(P,sizeof(int*)); //Aloca o Vetor 
		
		//Percorre as linhas do Vetor
 		for (int i=0; i < P; i++){ 
    		info.matriz[i] = (int*) calloc(P,sizeof(int)); 
		}

		info.vet_peso = (float*) malloc(sizeof(float)*P);
		info.vet_hab = (float*) malloc(sizeof(float)*P);
		
		int s = 0;
		info.P = P; 
		info.W= W; 
		info.C = C; 
		info.D = D;
		
		leitura(arquivo_input,&info);

		prop = peso(info.vet_peso,info.vet_hab,&P);

		pov_position = ordenacao(prop,&P);

		info.P = P; 
		info.W= W; 
		info.C = C; 
		info.D = D; 
		
		int *result = caminhos(pov_position,&s,&info); 
		//passa os parametros dados para fazer o calculo do caminho

		imprime(arquivo_output,result,&s);

		printf("\n");

		printf("resultado : \n \n");

		for(int i=0;i<s;i++) printf("%d ",result[i]);
		printf("\n\n");
	}

	//impressao do tempo final

	
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

	fclose(arquivo_input); //fecha os arquivos
	fclose(arquivo_output);

	return 0;
}