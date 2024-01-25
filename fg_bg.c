/************************************************************************************************
 *                                                                                              *
 * NAME         :KONIREDDY DHANUNJAYA REDDY                                                     *
 * DATE         :20/01/2023                                                                     *
 * FILE NAME    :FG_BG.C	                                                                *
 * DESCRIPTION  :THIS FILE IS USED TO MAKE THE PROCESS FOREGROUND AND BACKGROUND     		*
 *                                                                                              *
 ***********************************************************************************************/

#include "main.h"

extern int pid;
sll *bg_proc = NULL;
void execute_in_bg(sll **head)		//FUNCTION TO EXECUTE PROCESS IN BACKGROUND
{
	if(*head == NULL)		//CHECKING IF ANY BACKGROUND PROCCESSES ARE PRESENT
	{
		printf("No processes are stopped to run in background.\n");
		return;
	}
	if(kill((*head)->stop_pid , SIGCONT) < 0)
		perror("kill");		//SENDING CONTINUE SIGNAL TO run process in bg
	insert_sll((*head)->stop_pid , &bg_proc);
	delete_at_first(head);		//dDELETING THE PID FROM LINKED LIST
}

void execute_in_fg()
{
	if(bg_proc == NULL)		//CHECKING IF PROCESS IS IN BACKGROUND
	{
		printf("No process in background to run in foreground.\n");
		return;
	}
	//printf("i am in fg fun.\n");
	/*
	if(setpgid(bg_proc->stop_pid , bg_proc->stop_pid) == -1)
		perror("setpgid");
	if(tcsetpgrp(STDIN_FILENO,bg_proc->stop_pid));
	printf("%d %d .\n",bg_proc->stop_pid , getpgid(bg_proc->stop_pid));
	*/
	waitpid(bg_proc->stop_pid , NULL , WUNTRACED); //WAITING FOR THE PROCESS IF THE BACKGROUND PROCESS IS PRESENT
	pid = bg_proc->stop_pid;
	delete_at_first(&bg_proc);			//DELETING THE PID FROM BG_PROC
}

