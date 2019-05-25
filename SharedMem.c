#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//#include <sys/sem.h>

//#include <errno.h>

#define MAX_SHM_SZ  (8*1024)
#define SHM_PERMS   (S_IRWXU)



#ifdef CLIENT

int shmid;

int main(int argc, const char * argv[] )
{
	void * myShmPtr = 0;
	int tmp = 0;
	int cntr = 0;

	/* creating shm */
	if( (shmid = shmget(1234L, MAX_SHM_SZ, SHM_PERMS | IPC_CREAT | IPC_EXCL) ) < 0)
	{
		perror("failed to create shared memory.");
		return 0;
	}
    

    myShmPtr = shmat(shmid, (char*)0, 0666);
    if( myShmPtr < 0 )
    {
    	perror("failed to attach shared memory");
    	/* we are not removing shm from OS */
    	return 0;
    }


   // lets act like simple producer.
   do { 
    	sprintf(myShmPtr, "my Process:%s with pid %d wrote here %d times.\0", argv[0], getpid(), ++cntr);
    	printf("1. Write again\n0. exit\n");
    	scanf("%d", &tmp);
    } while ( tmp );

    /* detach my shm area. other can still access it */
    if ( shmdt(myShmPtr) < 0 )
    {
    	perror("failed to detach shared memory");
    }

    // lets mark to OS, to remove SHM whenever possible after me
    if( shmctl(shmid, IPC_RMID, (void*)0) < 0 )
    {
    	perror("failed to mark shared memory removal");
    }

    return 0;
}

#endif

#ifdef SERVER

int shmid;

int main(int argc, const char * argv[] )
{
	void * myShmPtr = 0;
	int tmp = 0;
	int cntr = 0;

	/* creating shm */
	if( (shmid = shmget(1234L, MAX_SHM_SZ, SHM_PERMS /*| IPC_CREAT | IPC_EXCL bcos we are server, i.e 2nd process */) ) < 0)
	{
		perror("failed to create shared memory.");
		return 0;
	}
    

    myShmPtr = shmat(shmid, (char*)0, 0666);
    if( myShmPtr < 0 )
    {
    	perror("failed to attach shared memory");
    	/* we are not removing shm from OS */
    	return 0;
    }

    // here we will act like simple consumer.
   do { 
    	printf("Read from Shm Area: %s\n", (char*)myShmPtr);
    	printf("1. Read again\n0. exit\n");
    	scanf("%d", &tmp);
    } while ( tmp );

    /* detach my shm area. other can still access it */
    if ( shmdt(myShmPtr) < 0 )
    {
    	perror("failed to detach shared memory");
    }

    // lets mark to OS, to remove SHM whenever possible after me
    if( shmctl(shmid, IPC_RMID, (void*)0) < 0 )
    {
    	perror("failed to mark shared memory removal");
    }

    return 0;
}



#endif
