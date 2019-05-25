#include<stdio.h>
#include<sys/file.h>
#include<stdlib.h>
#include <unistd.h>
#include<fcntl.h>
int main(){
	int pipefd[2],n;
	char buff[15];
	if(pipe(pipefd)<0)
		printf("error in creating pipe");

	printf("read fd =%d ,write fd= %d\n",pipefd[0],pipefd[1]);
	if(write(pipefd[1],"hello world\n",12)!=12)
		printf("error in writing to pipe");
	if((n=read(pipefd[0],buff,sizeof(buff)))<=0)
			printf("error in reading pipe");
	write(1,buff,n);
	exit(0);
}
	
