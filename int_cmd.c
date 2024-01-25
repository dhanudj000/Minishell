/************************************************************************************************
 *                                                                                              *
 * NAME         :KONIREDDY DHANUNJAYA REDDY                                                     *
 * DATE         :20/01/2023                                                                     *
 * FILE NAME    :INT_CMD.C                                                                      *
 * DESCRIPTION  :THIS FILE IS USED TO EXECUTE INTERNAL COMMAND.                                 *
 *                                                                                              *
 ***********************************************************************************************/

#include "main.h"

int execute_int_cmd(char *input)		//FUNTION TO EXECUTE INTERNAL COMMAND
{
    char *file;
    strtok(input , " ");			//MOVING TO NEXT OPTION FROM COMMAND
    if(!strcmp(input , "exit"))
    {
        exit(0);
    }
    else if(!strcmp(input , "pwd"))
    {
        printf("%s\n",get_current_dir_name());
    }
    else if(!strncmp(input , "cd" , 2))		//EXECUTING INTERNAL COMMANDS WITH SYSTEM CALLS
    {
        chdir(strtok(NULL , " "));
    }
    else if(!strncmp(input , "rmdir" , 5))
    {
        rmdir(strtok(NULL , " "));
    }
    else if(!strncmp(input , "mkdir" , 5))
    {
        mkdir(strtok(NULL , " "),0666);
    }
}
