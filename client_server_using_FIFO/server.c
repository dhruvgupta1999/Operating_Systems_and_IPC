#include "myhead.h"
#define fifo1 "/tmp/fifo.1"
#define fifo2 "/tmp/fifo.2"
#define PERMS 0666

int main(){
	int readfd,writefd;
	if((mknod(fifo1,S_IFIFO|PERMS,0)<0)&&(errno!=EEXIST))
		printf("cant create fifo: %s",fifo1);
	if((mknod(fifo2,S_IFIFO|PERMS,0)<0)&&(errno!=EEXIST))
	{
		unlink(fifo1);
		printf("cant create fifo: %s",fifo2);
	}

	if((readfd=open(fifo1,0))<0)
		printf("server: can't open read fifo: %s",fifo1);
	if((writefd=open(fifo2,1))<0)
		printf("server: cant open write fifo: %s",fifo2);
	server(readfd,writefd);
	close(readfd);
	close(writefd);

	exit(0);
}

void server(int readfd,int writefd){
	char buff[1024];
	int n,fd;
	extern int errno;

	if((n=read(readfd,buff,1024))<=0)
		printf("server: filename read error\n");
	buff[n]='\0';

	if((fd=open(buff,0))<0)
		printf("cant open file\n");
	else
	{
		while((n=read(fd,buff,1024))>0)
			if(write(writefd,buff,n)!=n)
				printf("server: data write error");
	if(n<0)
		printf("server: read error");
}
}
