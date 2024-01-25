/**************************************************************************************
 * NAME         :konireddy dhanunjauya reddy
 * DATE         :20/01/2023
 * FILE NAME    :main.c
 * DESCRIPTION  :the function is used to calll different functions according to input.
 *
 ***************************************************************************************/

#include "main.h"

void set_text_colour(char *colour)
{
    printf("%s" , colour);				//function to set text colour
}
sll *head = NULL;
extern int pid , exit_status;
void signal_handler(int signum , siginfo_t *info , void *input)
{							//function to handle signals
    switch(signum)
    {
        case SIGINT :
            if(pid > 0)
            {
                kill(pid , SIGINT);			//killing the process with pid using sigint
                exit_status = 128+SIGINT;
            }
            printf("\n");				//going to next line
            break;
        case SIGTSTP:
            if(pid > 0)
            {
                insert_sll(pid , &head);		//inserting piud to linked list
                if(kill(pid , SIGTSTP)!=0)
                    perror("kill");			//stopping the child using sigchld
                printf(" [%d]\t+stopped\n",pid);
                exit_status = 128+SIGTSTP;		//setyting exit status
            }
            printf("\n");
            break;
    }
}
int main()
{
    char input[50] = {"clear"},prompt[50]={"MiniShell$"};
    int cmd_status;
    char *ptr;
    printf(CLEAR); 
    struct sigaction act;
    act.sa_flags = SA_SIGINFO; 
    act.sa_sigaction = signal_handler;
    sigaction(SIGINT , &act , NULL  );
    sigaction(SIGTSTP , &act , NULL );
    act.sa_handler = SIG_DFL;				//setting signal to signal handlers
    act.sa_flags   = SA_NOCLDWAIT; 
    sigaction(SIGCHLD, &act, NULL);
    act.sa_handler = SIG_IGN;				//making the child not to become zombies
    act.sa_flags &= 0;
    //sigaction(SIGTTOU , &act , NULL);
    //sigaction(SIGTTIN , &act , NULL);
    while(1)
    {
        set_text_colour(GREEN);
        printf("%s ",prompt);				//printing prompt and reading input
        fflush(stdout);
        set_text_colour(RESET);
        fgets(input,50,stdin);
        ptr = strchr(input , '\n');			//checking if enter is entered
        if (ptr)
            *ptr = '\0';
        if (*input == '\0') 
        {
            continue;
        }
        if(strncmp(input,"PS1=",4)==0)
        {
            strcpy(prompt,input+4);			//copying the prompt when ps1 is read
        }
        else if(strcmp(input , "exit") == 0)
        {
            printf("exiting from minishell\n");		//exiting from minishell
            exit(0);
        }
        else if(strcmp(input , "echo $?") == 0)
        {
            printf("exit status : %d\n",exit_status);	//printing the exit status
        }
        else if(strcmp(input , "echo $$") == 0)
        {
            printf("%d\n",getpid());			//printing the pid
        }
        else if(strcmp(input , "echo $SHELL") == 0)
        {
            printf("%s/%s\n",get_current_dir_name(),prompt); //printing current directory
        }
        else if(!strcmp(input , "jobs"))
        {
            display_sll(head);				//printing the stopped process
        }
        else if(!strcmp(input , "bg"))
        {
            execute_in_bg(&head);			//executing the last stopped process in background
        }
	else if(!strcmp(input , "fg"))
	{
	    execute_in_fg();				//executing the last background process in foreground
	}
        else if(strchr(input , '|') != NULL)
        {
            execute_npipes(input);			//handling multiple pipes
        }
        else if((cmd_status =check_cmd(input)) == EXT_CMD)
        {
            execute_ext_cmd(input);			//executing external command
        }
        else if(cmd_status == INT_CMD)
        {
            execute_int_cmd(input);			//executing internal command
        }
        memset(input, 0, 50); 				//resetting the array with 0's
    }
}
