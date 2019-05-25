#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    int i;
    
    for( i=0;i<50;i++){

	printf("pid: %d  ppid:%d grpid:%d\n",getpid(),getppid(),getpgrp());
    sleep(10);
	}
}	
