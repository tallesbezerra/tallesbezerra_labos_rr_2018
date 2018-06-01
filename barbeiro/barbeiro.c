// linux
// compilar-> gcc -pthread barbeiro.c -o barbeiro
// executar-> ./barbeiro
//referencias https://en.wikipedia.org/wiki/Sleeping_barber_problem
//            http://www.ic.unicamp.br/~islene/2s2007-mo806/barbeiro/barbeiro.c

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"

#define N_CLIENTES 10

sem_t cad_barbeiro;
sem_t cadeiras;
sem_t cliente_cadeira;
int cadeiras_dis = 5;

void *f_barbeiro(){
	while(1){
		sem_wait(&cliente_cadeira);
		sem_wait(&cadeiras);
			cadeiras_dis += 1;
		printf("Barbeiro esta cortando cabelo\n");
		sem_post(&cad_barbeiro);
		sem_post(&cadeiras);
	}

	pthread_exit(NULL);

}

void *f_cliente(void* arg){
	int id = *(int*) arg;

	sem_wait(&cadeiras);
	if(cadeiras_dis > 0){
		printf("Cliente %d entrou na barbearia\n",id);
		sleep(1);
		cadeiras_dis -= 1;
		sem_post(&cliente_cadeira);
		sem_post(&cadeiras);
		sem_wait(&cad_barbeiro);
		printf("Cliente %d cortou o cabelo\n",id);
	}
	else{
		printf("Barbearia cheia, cliente %d foi embora\n",id);
		sem_post(&cadeiras);
	}

	pthread_exit(NULL);
}

int main(){
	sem_init(&cad_barbeiro,0, 0);
	sem_init(&cadeiras, 0, 1);
	sem_init(&cliente_cadeira, 0, 0);

	pthread_t thr_clientes[N_CLIENTES], thr_barbeiro;
	int i, id[N_CLIENTES];

	for(i=0; i<N_CLIENTES; i++){
		id[i] = i;
		pthread_create(&thr_clientes[i], NULL, f_cliente, (void*) &id[i]);
	}

	pthread_create(&thr_barbeiro, NULL, f_barbeiro, NULL);

	for(i=0; i<N_CLIENTES; i++){
		pthread_join(thr_clientes[i], NULL);
	}

	return 0;
}