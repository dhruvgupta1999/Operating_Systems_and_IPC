#include "myheader.h"
#include <signal.h>

int tmp=0;//to change back to dflt sig handler
void  mysighandler(int sig,siginfo_t * info,void * context ){
	printf("signal has been received\n");
	printf("sender pid: %d\n signal no:%d code:%d\n",info->si_pid,sig,info->si_code);/*printf is unsafe*/
    tmp=1;
}

int main(){

	struct sigaction  oldact;
	 struct sigaction  newact;

	 	memset(&newact, 0, sizeof(struct sigaction));
	 	memset(&oldact, 0, sizeof(struct sigaction));
	newact.sa_sigaction=mysighandler;
	sigfillset(&(newact.sa_mask));
	newact.sa_flags=SA_NODEFER|SA_SIGINFO;

	if(sigaction(SIGINT,&newact,&oldact)==-1)
		printf("sigaction malfunction\n");
	while(1)
	{
		sleep(1);
	if(tmp==1)
        	sigaction(SIGINT,&oldact,&newact);


	}
}

















