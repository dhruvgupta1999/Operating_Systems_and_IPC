#include "myhead.h"
#include <sys/ipc.h>
#include <sys/msg.h>

#define key ((key_t) 12345L)
#define perms 0666

int main(){
	int i,msgqid;
	for(i=0;i<10000;i++)
	{
		if( (msgqid=msgget(key,perms|IPC_CREAT))<0)
			printf("cant create msgqueue\n");
		printf("msgqid=%d\n",msgqid );
		if(msgctl(msgqid,IPC_RMID,(struct msqid_ds *) 0))
			printf("cant remove msgq\n");

	}
}
