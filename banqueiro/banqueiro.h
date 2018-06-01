struct processo{
	int id;
    int r_usando;
    int r_max;
    struct processo *proximo;
};
typedef struct processo pro;

pro* criar_pro(pro *p, int *r_disponiveis, int id){
	pro* novo = (pro*)malloc(sizeof(pro));
	printf("Quant de recursos utilizados:	");
	scanf("%d",&(novo)->r_usando);
	printf("Quant de recursos requeridos:	");
	scanf("%d",&(novo)->r_max);
	printf("\n");
	novo->id = id;
    novo->proximo = NULL;
    *r_disponiveis = *r_disponiveis-novo->r_usando;

	if (p==NULL)
		p = novo;
	else{
		pro *aux;
		for (aux = p; aux->proximo!=NULL; aux=aux->proximo){}
        aux->proximo = novo;
	}
    return p;
}

pro* remover(pro *p, pro *aux){
	pro *atual,*ant;
	ant = NULL;
	for(atual=p; atual!=NULL; atual=atual->proximo){
		if(atual==aux){
			if(ant==NULL){
				ant = atual->proximo;
				free(atual);
				return ant;
			}
			else{
				ant->proximo = atual->proximo;
				free(atual);
				return p;
			}
		}
		ant = atual;
	}
	return p;
}

void mostrar(pro *l){
    pro *aux;
	for (aux = l; aux!=NULL; aux=aux->proximo){
		printf("Processo %d\n", aux->id);
		printf("Quant de recursos utilizados:	%d\n", aux->r_usando);
		printf("Quant de recursos requeridos:	%d\n", aux->r_max);
	}
}