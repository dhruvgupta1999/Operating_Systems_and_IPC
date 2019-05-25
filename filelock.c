#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <string.h>
void mylock(int);
void unlock(int);

int main(){
	 int i,pid,fd,seqno,n;

     char bffl[10];
	 pid=getpid();
	 
	 if((fd=open("./seqno",2))<0)
			 printf("error opening shared resource\n");
     mylock(fd);
	 for( i=0;i<20;i++)
	 {
		 lseek(fd,0,0);
		 n=read(fd,bffl,10);
         n=sscanf(bffl,"%d\n",&seqno);
		 printf("pid== %d seq#= %d\n",pid,seqno);
		 seqno++;
		 sprintf(bffl,"%d\n",seqno);
		 n=strlen(bffl);
		 lseek(fd,0l,0);
		 write(fd,bffl,n);
	 }
	 unlock(fd);
}

void mylock(int fd)
{
	flock(fd,LOCK_EX);
}

void unlock(int fd){
	flock(fd,LOCK_UN);
}






	
	 


