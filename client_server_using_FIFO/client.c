#include "myhead.h"
#define fifo1 "/tmp/fifo.1"
#define fifo2 "/tmp/fifo.2"


int main(){
	int readfd,writefd;

	if((writefd=open(fifo1,1))<0)
		printf("client: cant open fifo: %s",fifo1);
	if((readfd=open(fifo2,0))<0)
		printf("client: cant open readfd: %s",fifo2);
	client(readfd,writefd);
	close(readfd);
		close(writefd);

	if(unlink(fifo1)<0)
		printf("client: cant unlink %s",fifo1);
	if(unlink(fifo2)<0)
		printf("client: cant unlink %s",fifo2);
	exit(0);
}

void client(int readfd,int writefd)
{
	char buff[1024];
	int n;
	if(fgets(buff,1024,stdin)==NULL)
		printf("client: filename read errror");
	n=strlen(buff);
	if(buff[n-1]=='\n')
		n--;
	if(write(writefd,buff,n)!=n)
		printf("client: filename write error");
	while((n=read(readfd,buff,1024))>0)
			if(write(1,buff,n)!=n)
			printf("client: data write error");
	
	if(n<0)
	printf("client: data read error");
	}

