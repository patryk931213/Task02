#include <stdio.h>
#include <pthread.h>

pthread_mutex_t MTX = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int ping = 1;
int count = 0;
int arg;
void*pingPong(void*);

int main(int argc, char ** argv){
	if(argv[1])
		arg = atoi(argv[1]);
	pthread_t thread[2];
	pthread_create(&thread[0],0, pingPong, &c);
	pthread_create(&thread[1],0, pingPong, &c);	
	
	printf("");
	pthread_cond_signal(&c);
	pthread_mutex_unlock(&MTX);
	
	pthread_join(thread[0], NULL);	
	pthread_join(thread[1], NULL);	
}


void * pingPong(void * val){
	while(1){
		if(count>arg) break;
		pthread_cond_t * mutex = (pthread_cond_t*)val;
		pthread_mutex_lock(&MTX);
		pthread_cond_wait(mutex, &MTX);
		if(ping == 1){ 
			printf("Ping\n");
			ping = 0;
		}
		else{
			printf("\tPong\n");
			ping = 1;		
		}
		//sleep(1);
		pthread_cond_signal(&c);
		pthread_mutex_unlock(&MTX);
		count++;
	}
}

