#include  <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
char history[10][100];
int count = 0;
void displayHistory()
{
    
    printf("Shell command history:\n");
    
    int i;
    int j = 0;
    int histCount = count;
    for (i = 0; i<10;i++)
    {
        printf("%d.  ", histCount);
        while (history[i][j] != '\n' && history[i][j] != '\0')
        {	
            printf("%c", history[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        histCount--;
        if (histCount ==  0)
            break;
    }
    printf("\n");
} 
void  parse(char *line, char **argv)
{
     while (*line != '\0') {       
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     
          *argv++ = line;          
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;          
     }
     *argv = '\0';                 
}
void  execute(char **argv)
{
     pid_t  pid;
     int    status;
     
     if ((pid = fork()) < 0) {     
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {        
          if (execvp(*argv, argv) < 0) {     
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  
          while (wait(&status) != pid);
     }
}
     
int  main()
{
     char  line[1024];             
     char  *argv[64];              
     
     while (1) {                   
          printf("Shell -> ");     
          gets(line);
          // scanf("%[^\n]s ",line); 
	if(count>10) count=10;            
          printf("\n");
          parse(line, argv); 
	if(strcmp(argv[0],"history")==0)
        {		
               if(count>0)
		{
		
                displayHistory();
		}
		else
		{
		printf("\nNo Commands in the history\n");
		}
        }
	else if(strcmp(argv[0],"cd")==0)//one is just a string from the user input
	    {
		chdir(argv[1]);
	    }
          else if (strcmp(argv[0], "exit") == 0) 
               exit(0);           
          else {
		execute(argv);
	}         
	for (int i = 9;i>0; i--) 
       		strcpy(history[i], history[i-1]);
    
    	strcpy(history[0],line); 
    	count++;
     }
     return 0;
}