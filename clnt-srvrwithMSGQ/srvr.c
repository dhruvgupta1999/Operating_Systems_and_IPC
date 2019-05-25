#include "myheader.h"
#include <sys/ipc.h>
#include <sys/msg.h>
extern int errno;
#define mkey1 1234l
#define mkey2 2345l
#define perms 0666

struct mymsgbuff{
    int mlen;
    long mtype;
    char mtext[1024];
};


struct mymsgbuff Msg;

int main(){
	int id;
	struct mymsgbuff * ptr=&Msg;
	if((id=msgget(mkey1,perms|IPC_CREAT))<0)
	{
		perror("server: cant create msg queue");
        return errno; 
	}
	int n,filefd;
	Msg.mtype=1l;
	if((n=msgrcv(id,(char *) &(ptr->mtype),1024,Msg.mtype,0))<=0)
		printf("server: filename read error\n");
   // Msg.mtext[n]='\0';
   printf("filename received is: %s\n",Msg.mtext);
	Msg.mtype=2l;
    if((filefd=open(Msg.mtext,0))<0)
    	printf(": cant open\n");
    else{

    	while((n=read(filefd,Msg.mtext,1024))>0)
    	{
    		Msg.mlen=n;
    		if(msgsnd(id,(char *)&(ptr->mtype),ptr->mlen,0)!=0)
    			printf("server: msgsend error\n");
    	}
    	close(filefd);
        if(n<0)
        printf("servr:read error\n");    	
    }

    Msg.mlen=0;
    if(msgsnd(id,(char *)&(ptr->mtype),0,0)!=0) 
    			printf("server: msgsend error\n");
	else printf("Terminating\n");
}
