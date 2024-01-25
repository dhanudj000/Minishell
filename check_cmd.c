/************************************************************************************************
 * 												*
 * NAME		:KONIREDDY DHANUNJAYA REDDY							*
 * DATE		:20/01/2023									*
 * FILE NAME	:CHECK_CMD.C									*
 * DESCRIPTION	:THIS FILE IS USED TO CHECK IF THE COMMAND IS INTERNAL OR EXTERNAL COMMAND.	*
 *												*
 ***********************************************************************************************/

#include "main.h"

char *int_cmd[] = {"cd" , "pwd" ,"exit" , "rmdir" , "mkdir" , NULL};	//ARRAY TO CHECK IF THE INPUT IS INTERNAL COMMAND
int  check_cmd(char *input)
{
	char array[strlen(input)+1];					//ARRAY TO READ THE COMMAND UPTO FIRST SPACE
	strcpy(array , input);
	char *cmd = strtok(array , " ");
	for(int i=0;int_cmd[i]!=NULL;i++)				//CHECKING IF IT IS IN INT CMD ARRAY
	{
		if(!strcmp(cmd , int_cmd[i]))
		{
			return INT_CMD;					//COMPARING AND RETURNING THE RESULT
		}
	}
	return EXT_CMD;	
}

void get_cmd(char *input , char *cmd[])					//FUNCTION TO READ COMMAND AND ARGUMENTS
{
	char *token = strtok(input , " ");				//SEPERATING COMMANDS AND ARGUMENTS BASED ON SPACING
	for(int i=0;token != NULL ; i++)
	{
		cmd[i] = malloc(strlen(token)+1);			//ALLOCATING THE MEMORY TO STORE THE COMMAND
		strcpy(cmd[i] , token);					//COPYING THE COMMAND
		token = strtok(NULL , " ");
	}
}
