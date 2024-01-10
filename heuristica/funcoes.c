#include "bibliotecas.h"
//funcao para fazer o calculo de quais caminhoes terao a melhor resultcao
int *caminhos(int *pov_position,int *S, DADOS *info){
	
	int D = info->D;
	int W = info->W;
	int P = info->P;

	int tam = P *2;
	tam++;
	int *result = (int *) malloc(sizeof(int)*tam);

	int j=0;
	int i=0;

	for(j=0;j<i+1;j++) result[j] = 0;

	int s=0;

	s=1;

	int peso_atual = 0;
	int dist_atual = 0;
	int soldado = 0;

	int povo;
	//escolhe o povo com melhores capacidades
	povo = pov_position[0];
	int povo_ant = -1;

	int k=0;
	do{
		do{
			soldado++;
			result[0] += info->vet_hab[povo];
			peso_atual += info->vet_peso[povo];
			i++;
		}while(peso_atual<=W);

		if(peso_atual==W) break;
		
		result[0] -= info->vet_hab[povo];
		peso_atual -= info->vet_peso[povo];
		soldado--;
		

		result[s] = povo+1;
		s = s+1;
		result[s] = soldado;
		s = s+1;

		//depois de salvar a nova solucao a distancia é acumulada e testada
		if(povo_ant!=-1){ //só testa quando ja tem mais de um povo

			dist_atual += info->matriz[povo_ant][povo];

			if(dist_atual==D) break;

			if(dist_atual>D){
				dist_atual -= info->matriz[povo_ant][povo];
				s--;
				result[s] = 0;
				s--;
				result[s] = 0;
				break;
			}
		}
		//comparacao com os dados da matrix
		for(i=0;i<P;i++){
			if(info->matriz[povo][i]!=0) break;
		}
		if(i==P) break;

		povo_ant = povo;
		povo = i;

		soldado = 0;

		k++;
	}while(k<tam && i<P);

	(*S) = s;

	return result;
}

float *peso(float *peso, float *hab, int *P){
	float *prop = (float *) malloc(sizeof(float) * (*P));

	for(int i=0;i<*P;i++){
		prop[i] = peso[i]/hab[i];
	}

	return prop;
}

void imprime(FILE *arquivo_output, int *result, int *s){

	int k = 0;
	do{
		fprintf(arquivo_output,"%d",result[k]);
		fprintf(arquivo_output,"%s"," ");
		k++;
	}while(k<*s);
	fputc('\n',arquivo_output);
}

int *ordenacao(float *vet, int *P){

//	int *aux = (int *) malloc(sizeof(int)*(*P)); não precisa
	float aux;
	int teste;
	int *pov_position = (int *) malloc(sizeof(int)*(*P));

	for(int i=0;i<*P;i++) pov_position[i] = i;

	for(int i=0;i<*P;i++){
		for(int j=0;j<*P;j++){
			if(vet[j]>vet[i]){
				aux = *(vet+i);
				*(vet+i) = *(vet+j);
				*(vet+j) = aux;

				aux = pov_position[i];
				pov_position[i] = pov_position[j];
				pov_position[j] = aux;
			}
		} 
	}

	return pov_position;

}
//colocaçao dos dados e da matriz no arquivo
void leitura(FILE *arquivo_input, DADOS *info){
	int P = info->P;
	int C = info->C;
	int i=0;
	int descarte;

	for(i=0;i<P;i++){

		fscanf(arquivo_input,"%d",&descarte);
		fscanf(arquivo_input,"%f",&info->vet_peso[i]); //preenche um vetor com pesos
		fscanf(arquivo_input,"%f",&info->vet_hab[i]); //preenche o vetor com as habilidades
	}

	for(i=0;i<P;i++){
		printf("povo %d : %.0f ",i+1,info->vet_peso[i]);
	}
	printf("\n");

	for(i=0;i<P;i++){
		printf("povo %d : %.0f ",i+1,info->vet_peso[i]);
	}
	printf("\n");


	int povoi,povoj;

	for(i=0;i<C;i++){

		fscanf(arquivo_input,"%d",&povoi);
		fscanf(arquivo_input,"%d",&povoj);

		printf("%d - %d\n",povoi,povoj);
		fscanf(arquivo_input,"%d",&info->matriz[povoi-1][povoj-1]);
	}
	printf("\n\n");

	for(int i=0;i<P;i++){
		for(int j=0;j<P;j++){
			if(info->matriz[i][j]==0) info->matriz[i][j] = info->matriz[j][i];
		}
	}

}