#include "main.h"

#define ERROR -1
#define CHILD 0

int find_pipes(char *str , char *argv[]  ,int *cmd_arr);                            //FUNCTION TO FIND WHERE ARE COMMANDS AND PIPES

void  execute_npipes(char *str)
{
        int cmd_index[10] , child;                                      //LOCATING COMMANDS INDEX
        cmd_index[0] = 0;
	char *argv[20];
        int pipes_count = find_pipes(str , argv  , cmd_index);
        if(pipes_count == 0)
		return;
	int pipefd[pipes_count][2];                                     //CREATING PIPES TO COMMUNICATE
        for(int i=0 ; i<pipes_count ; i++)
        {
        pipe(pipefd[i]);
        printf("created pipe - %d %d\n",pipefd[i][0],pipefd[i][1]);
        }
        switch(child = fork())                                          //CREATING CHILD
        {
                case ERROR:
                        perror("fork");                                 //PRINTING ERROR ID CHILD IS NOT CREATED
                        exit(0);
                case CHILD:
                        for(int i=0 ; i<pipes_count ; i++)              //ITERATING NO.OF.PIPE TIMES
                        {
                                switch(fork())
                                {
                                        case ERROR:                     //CREATING CHILDREN INSIDE CHILD
                                                perror("fork");
                                                exit(0);
                                        case CHILD:
                                                if(i != 0)              //REPLACING STDIN WITH PIPE
                                                {
                                                        dup2(pipefd[i-1][0] , 0);
                                                        close(pipefd[i-1][0]);
                                                        perror("dup2"); //CLOSING UNUSED END
                                                }
                                                dup2(pipefd[i][1] , 1); //REPLACING STDOUT WITH PIPE
                                                close(pipefd[i][1]);
                                                perror("dup2");         //CLOSING UNUSED END
                                                execvp(argv[cmd_index[i]] , argv + cmd_index[i]);
                                                perror("execvp");
                                                exit(1);
                                        default:                        //EXECUTING THE COMMAND
                                                close(pipefd[i][1]);    //CLOSING WRITING END IN PARENT CHILD
                                                wait(NULL);
                                }
                        }
                                dup2(pipefd[pipes_count-1][0],0);       //REPLACING STDIN WITH LAST READ PIPE
                                perror("dup2");
                                printf("cmd o/p : \n\n");               //PRIINTING THE FINAL OUTPUT
                                execvp(argv[cmd_index[pipes_count]] , argv + cmd_index[pipes_count]);
                                perror("execvp");
                                exit(2);

                default   :
                        for(int i=0 ; i<pipes_count ; i++)              //CLOSING ALL PIPES IN PARENT
                        {
                                close(pipefd[i][0]);
                                close(pipefd[i][1]);
                        }
                        waitpid(child,NULL,0);                          //WAITING FOR THE FIRST CHILD
        }
}

int find_pipes(char *str , char *argv[] , int *cmd_arr)                             //FUNCTION TO FIND PIPES AND COMMANDS
{
        int count = 0,j=1,i=0,k=0;
	char *ptr = strtok(str , " ");
	while(ptr!=NULL)
	{
		if(strcmp(ptr , "|") == 0)
		{
			argv[k++] = NULL;
			cmd_arr[j++] = i+1;
			count++;
		}
		else
		{
			argv[k++] = ptr;
		}
		ptr = strtok(NULL , " ");
		i++;
	}
	argv[k] = NULL;
        
        for(int i=0; i<count+1 ; i++)                                   //PRINTING THE INDICES INSIDE CMD_ARRAY
                printf("cmd at %d\n",cmd_arr[i]);
        if(count == 0)
        {
                printf("Error: No arguments passed,Provide atleast one pipe  or more\nUsage: <command1><space>|<space><command2>\nUsage: <command1><space>|<space><command2><space>|<space><command3> etc\n");
        }
        return count;                                                   //RETURNING NO.OF PIPES FOUND
}

