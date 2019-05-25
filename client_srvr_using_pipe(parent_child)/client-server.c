#include "myhead.h"

void client(int pipe1[2],int pipe2[2]);
void server(int pipe1[2],int pipe2[2]);
int main(){
	char *buff=malloc(1510*sizeof(char));
    int childpid,pipe1[2],pipe2[2],n;
	if(pipe(pipe1)<0 || pipe(pipe2)<0)
		printf("cant create pipes\n");

	if((childpid=fork())<0)
		printf("error in forking\n");
	else if(childpid>0)
	{
        close(pipe1[0]);
		close(pipe2[1]);
	
	    client(pipe1,pipe2);
		wait((int*)0);
		close(pipe1[1]);
		close(pipe2[0]);
	}
	else
	{
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1,pipe2);
		close(pipe1[0]);
		close(pipe2[1]);
		exit(0);
	}
}

void client(int pipe1[2],int pipe2[2])
{
	
	
	char buff[1510];
	printf("enter input:\n");
	if(fgets(buff,15,stdin)==NULL)
		printf("client: error reading filename\n");
	int n=strlen(buff);
	if(buff[n-1]=='\n')
		n--;
	if(write(pipe1[1],buff,n)!=n)
		printf("error in writing to pipe1");
     //	wait(NULL);

	if(read(pipe2[0],buff,1500)<=0)
         printf("error in reading from pipe2");
    n=strlen(buff);
	printf("output:\n");
	write(1,buff,n); //giving output to user
}

void server(int pipe1[2],int pipe2[2])
{
	//sleep(1); note: read(2) is blocked till data is available in pipe (see pipe man page)
	char buff[1510];
	read(pipe1[0],buff,15);
	int n=strlen(buff);
	int fd;
	if((fd=open(buff,0))<0)
		printf("error in opening file\n");
	read(fd,buff,1500);
    write(pipe2[1],buff,1500);
	
	exit(0);
}

