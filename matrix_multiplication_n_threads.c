#include <stdio.h>
#include <string.h>
// #include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int n;
int a[1000][1000];
int b[1000][1000];
int c[1000][1000];
int d[1000][1000];
pthread_mutex_t lock; 
int counter=0;

void* calc_row(void* arg) 
{ 
	int sum;
	pthread_mutex_lock(&lock);
	int i=counter++;
	pthread_mutex_unlock(&lock);
	for (int j = 0; j < n; ++j)
	{
		sum=0;
		for (int k = 0; k < n; ++k)
		{
			sum+=(a[i][k]*b[k][j]);
		}
		c[i][j]=sum;

	}

	return NULL;
} 


int main()
{
	if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
	printf("enter matrix size\n");
	scanf("%d",&n);

	// Generating random values in matA and matB 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) { 
			a[i][j] = rand() % 10; 
			b[i][j] = rand() % 10; 
		} 
	}
	int sum=0;
	double total_time;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < n; ++i)
    {
    	for (int j = 0; j < n; ++j)
    	{	sum=0;
    		for (int k = 0; k < n; ++k)
    		{
    			sum+=(a[i][k]*b[k][j]);
    		}
    		d[i][j]=sum;
    	}
    }
    end = clock();
    double CLK_TCK = 1000000.0;
    total_time = ((double) (end - start)) / CLK_TCK;

    printf("For execution without explicit threading,time taken is:%f\n",total_time);

    pthread_t threads[n];
    start = clock();
    for (int i = 0; i < n; ++i)
    {
    	pthread_create(&threads[i], NULL,calc_row,NULL);
    }
    for (int i = 0; i < n; ++i)
    {
    	pthread_join(threads[i], NULL);
    }
    end = clock();
    total_time = ((double) (end - start)) / CLK_TCK;

    printf("For execution using n(no.of rows) threads:%f\n",total_time);
	pthread_mutex_destroy(&lock);

}
