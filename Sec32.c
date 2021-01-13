// Please read all the comments in this code for instruction
/* The announce lab quiz policy applies to this lab quiz.
The following piece of code creates a sorted linked list with 3, 4, 5, 6. A simplePrint function is used to print the data in the linked list. You can run and test the content of the linked list.

What you have to do:

There are two blank functions bellow that you should complete based on the requirements described as comments inside the function.
To test your function you may or may not need to uncomment/add lines in main function. Compare your result with the comment given in main function.

After completing the code and testing, submit the modified file in webocurses before the due time.
Caution: No code will be accepted in email if you miss the deadline. Also do not share your code as sharing will be considered as dishonesty and will be treated accordingly.

                   Write your name here: Gregory Freitas 
                   your UCFID: ------

*/


#include<stdio.h>
#include<stdlib.h>

 typedef struct nod{
	int info;
	struct nod *next;
}node;

node* SortInsert(node *root, int item); //this function is complete
void simplePrint(node* root); //this function is complete
int countNodes (node* root); //you have to write this function, see bellow //total grade 5
node* EvenCopy(node * root); //you have to write this function, see bellow // total grade 5



int main()
{
    node* head=NULL;
	node* head2 = NULL;

	node *t;
	int ch,ele;
	head = SortInsert(head, 4);
	head = SortInsert(head,6);
	head = SortInsert(head,3);
	head = SortInsert(head,5);

    printf("\nSimple print List 1: ");
    simplePrint(head);

     printf("\nCount Nodes %d", countNodes(head)); //modify the countNodes function to make it work

    head2 = EvenCopy(head); //modify the  EvenCopy function to make it work
    printf("\nSimple print after EvenCopy: ");
    simplePrint(head2); //This call should print 4, 6


	return 0;

}

void simplePrint(node* root)
{
    node* t=root;
    while(t!=NULL)
    {
        printf("%d ",t->info);
        t=t->next;
    }
}

node*  SortInsert(node* root, int item)
{
    node *temp;
    node *t;
    temp= (node *) malloc(sizeof(node));
    temp->info=item;
    temp->next=NULL;
    if (root==NULL || root->info >=item)
    {
            temp->next = root;
            root = temp;
    }
    else
    {
         t = root;
         while (t->next != NULL && t->next->info <item)
                   t = t->next;
         temp->next = t->next;
         t->next = temp;
    }

    return root;
}

///////// All questions are starting here//////////////////



int countNodes (node* root)
{
    /*this function takes the head of a linked list and returns the number of nodes available in the linked list */
    node *t = root;
    int count = 1;
    
    while(t->next != NULL)
    {
      t = t->next;
      count++;
    }

    return count; //this is dummy return. remove it when you change your code
}


node* EvenCopy(node * root)
{
    /*this function takes the head of a linked list and copies all the even numbers to a new linked list and return the
    head of the new linked list. Note that a number is considered as even if number%2 is 0.
    Example: passing the head of a linked list containing 3, 4, 5, 6 would return another linked list containt the 4, 6 */
    node *t = root;
    node *temp = NULL;
    
    while(t != NULL)
    {
      if((t->info % 2) == 0)
      {
      
        temp = SortInsert(temp, t->info);
        
      }
      else
      {
        // ignore since it is not an even number.
        //printf("Uneven number.\n");
      }
      t = t->next;
    }
    

    return temp; //this is dummy return. remove it when you change your code

}


