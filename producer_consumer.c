// #include <bits/stdc++.h>
#include <stdio.h>
#include<string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>


sem_t produce,consume,mutex;
char buf[10];int flag=0;

void * producer(void * arg)
{
	
	char str[100]="Jack and Jill went up the hill to fetch a pail of water.\n\0";
	int i=0,counter=0;
	while(str[i])
	{
		sem_wait(&produce);
		// sem_wait(&mutex);
		buf[counter]=str[i];
		// sem_post(&mutex);
		counter=(counter+1)%10;
		sem_post(&consume);
		i++;
		// printf("in producer\n");
	}
	flag=1;
}

void * consumer(void * arg)
{
	
	int counter=0;
	int sval;
	sem_getvalue(&consume,&sval);
	// printf("in consumer\n");
	while(flag==0 || sval!=0)
	{

		sem_wait(&consume);
		// sem_wait(&mutex);
		printf("%c",buf[counter]);
		counter=(counter+1)%10;
		// sem_post(&mutex);
		sem_post(&produce);
		sem_getvalue(&consume,&sval);

	}
}

int main()
{
	sem_init(&produce, 0, 10) ;
    sem_init(&consume, 0, 0) ;
    // sem_init(&mutex, 0, 1) ;
	pthread_t threads[2];
	pthread_create(&threads[0], NULL,producer,NULL);
	pthread_create(&threads[1], NULL,consumer,NULL);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

}