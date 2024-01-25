typedef struct node
{
   int stop_pid;
   struct node *next;
}sll;
 
void delete_at_first(sll **head);
void insert_sll(int data , sll **head);
void display_sll(sll* head);
