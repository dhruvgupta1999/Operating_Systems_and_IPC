#include "myheader.h"
#include <sys/ipc.h>
#include <sys/msg.h>
extern int errno;
#define mkey1 1234l
#define mkey2 2345l
#define perms 0666

extern int errno;
struct mymsgbuff {
    int mlen;
    long mtype;
    char mtext[1024];
};

struct mymsgbuff Msg;

int main()
{
    int id;
    if ((id = msgget(mkey1, 0)) < 0)
    {
	perror("can't get message for given key");
	return errno;
    }
    struct mymsgbuff *ptr = &Msg;
    ptr->mtype = 1L;

    printf("enter file name:\n");
    if ((fgets(ptr->mtext, 1024, stdin)) == NULL)
	{

perror("client:error in accepting filename\n");
		msgctl(id, IPC_RMID, NULL);
	return errno;
	}



    int n = strlen(ptr->mtext);
    if (ptr->mtext[n - 1] == '\n')
	n--;
    ptr->mtext[n] = '\0';
    ptr->mlen = n+8;




    printf("filename sent is: %s\n", Msg.mtext);

    if (msgsnd(id, (char *) &(ptr->mtype), ptr->mlen, 0) != 0)
	printf("client:msgsnd error");

    Msg.mtype = 2l;
    while ((n =
	    msgrcv(id, (char *) &(ptr->mtype), 1024, ptr->mtype, 0)) > 0) {
	if (write(1, Msg.mtext, n) != n)
	    perror("data write error\n");
	}
    if (n < 0){

	perror("data read error\n");
	}

	msgctl(id, IPC_RMID, NULL);

}
