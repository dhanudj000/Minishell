/************************************************************************************************
 *                                                                                              *
 * NAME         :KONIREDDY DHANUNJAYA REDDY                                                     *
 * DATE         :20/01/2023                                                                     *
 * FILE NAME    :EXT_CMD.C                                                                    	*
 * DESCRIPTION  :THIS FILE IS USED TO EXECUTE EXTERNAL COMMAND.     				*
 *                                                                                              *
 ***********************************************************************************************/

#include "main.h"
#include <errno.h>

int exit_status,pid;
//VARIABLES RO READ EXITSTATUS AND PIS OF CHILD
void set_text_colour(char *colour);

int execute_ext_cmd(char *input)
{
    int ret;
    char *cmd[10] = {NULL};
    switch(pid = fork())						//CREATING CHILD
    {
        case 0  :
            get_cmd(input , cmd);
            if(execvp(cmd[0] , cmd) == -1)				//EXECUTING THE COMMAND AFTER SEPEARTING THE INPUT
            {
                printf("%s : command not found.\n",cmd[0]);
            }
            break;
        case -1 :
            perror("fork");						//PRINTING IF ANY ERROR OCCURS
            return 0;
        default :
            ret = waitpid(pid , &exit_status , WUNTRACED);		//COLLECTING THE RETURN VALUE TO CHECK IF THERES ANY ERROR
            /*
	    if(errno == ECHILD)
                printf("ECHILD\n");
            if(errno == EINVAL)
                printf("EINVAL\n");
            if(errno == EINTR)
                printf("EINTR\n");
	    */
            if(WIFEXITED(exit_status))					//CHECKING WHICH CAUSE THE CHILD TO COME OUT OF IT
            {
                set_text_colour(GREEN);
                printf("the child %d terminated normally with status %d.\n",pid,WEXITSTATUS(exit_status));
                return WEXITSTATUS(exit_status);			//CHECKING IF ITS NORMALLY TERMINATED
            }
            else if(WIFSTOPPED(exit_status))
            {
                set_text_colour(MAGENTA);				//CHECKING IF IT IS STOPPED BY A SIGNAL
                printf("the child %d stopped by %d.\n",pid,WSTOPSIG(exit_status));
            }
            else if(WIFSIGNALED(exit_status))
            {
                set_text_colour(YELLOW);				//CHECKING IF ANY SIGNAL CAUSED THE TERMINATION
                printf("the child %d terminated by recieving signal %d.\n",pid,WTERMSIG(exit_status));
            }
            set_text_colour(RESET);
            pid = 0;							//RESETTING TEXT XOLOUR AND EXIT STATUS
            exit_status = 0; 

    }
}

