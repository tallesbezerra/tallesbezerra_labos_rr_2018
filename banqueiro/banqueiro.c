//Linux
//compilar -> gcc banqueiro.c -o banqueiro
//executar -> ./banqueiro

#include <stdio.h>
#include <stdlib.h>
#include "banqueiro.h"

void verifica_processos(pro *processos, int *r_disponiveis, int *n_pro_atual){
	pro *aux;
	for (aux=processos; aux!=NULL; aux=aux->proximo){
		if ((aux->r_max - aux->r_usando) <= *r_disponiveis){
			printf("\nRecursos disponiveis:	%d\n", *r_disponiveis);
			mostrar(processos);
			*r_disponiveis = *r_disponiveis + aux->r_usando;
			processos = remover(processos,aux);
			*n_pro_atual -= 1;
		}
	}
}

int main(){
    int i;
    int r_disponiveis, n_processos, n_pro_atual;
    pro *processos = NULL;
    printf("Quant. de processos:	");
    scanf("%d",&n_processos);
    printf("Quant. de recursos:	");
    scanf("%d",&r_disponiveis);

    for(i=0;i<n_processos;i++){
    	printf("Processo %d\n", i+1);
        processos = criar_pro(processos,&r_disponiveis,i+1);
    }
    n_pro_atual = n_processos;

    while(n_processos!=0){
    	//Percorre a lista com os processos verificando aqueles que podem utilizar os recursos sem
		//compromenter os outros
		//Se ao passar por todos os processos, nenhum foi finalizado, o estado é inseguro
		//pois os recursos foram mal distribuidos e os recursos disponiveis são insuficientes para
		//qualquer processo
    	pro *aux;
        verifica_processos(processos,&r_disponiveis,&n_pro_atual);
        if(n_pro_atual == n_processos){
        	printf("Recursos disponiveis %d\n", r_disponiveis);
            printf("Estado inseguro!!!!\n");
            return 0;
        }
        n_processos = n_processos - (n_processos - n_pro_atual);
    }
    printf("Estado seguro!!\n");
    return 0;

}
