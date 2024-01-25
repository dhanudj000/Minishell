/**************************************************************************************
 * NAME		:konireddy dhanunjauya reddy
 * DATE		:20/01/2023
 * FILE NAME	:linked_list.c
 * DESCRIPTION	:the function is used to create and operate linked list
 *
 ***************************************************************************************/
#include "main.h"


void insert_sll(int data , sll **head)		//function to create a linked list
{
    sll *new = malloc(sizeof(sll));
    new->stop_pid = data;
    new->next = NULL;				//allocating memory to node
    if(*head == NULL)
    {
        *head = new;				//if element is first then set head value
        return;
    }
    sll *temp = *head;
    while(temp->next)				//else connect the head and next node
    {
        temp = temp->next;
    }
    temp->next = new;				//return
    return;
}

void delete_at_first(sll **head)
{
	if(*head == NULL)			//checking if linked list is null
		return;
	sll *temp = *head;
	*head = (*head)->next;			//set head to next node
	free(temp);
}
void display_sll(sll* head)
{
    while(head != NULL)				//print the pids until last node
    {
        printf("[%d]+\tstopped.\n",head->stop_pid);
        head = head->next;
    }
}
