/* COP 3502C Midterm Assignment Two This program is written by: Gregory Freitas */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int sequenceNumber;
  struct Node *next;
  struct Node *previous;
  
} Soldier;


// Intiailize a soldier node with the given sequence.
Soldier *Create_Soldier(int sequence)
{
  Soldier *temp = (Soldier *) malloc(sizeof(Soldier));
  temp->sequenceNumber = sequence;
  temp->next = NULL;
  temp->previous = NULL;
  
  return temp;
}

Soldier *Insert_Front(Soldier *root, Soldier *newSoldier)
{
  Soldier *newItem = root;
  
  // Was no items in list.
  if(newItem == NULL)
  {
    root = newSoldier;
    root->next = root;
    root->previous = root;
  }
  else
  {
    Soldier *t;
    
    t = root;
    while(t->next != root)
      t = t->next;
    
    t->next = newSoldier;
    newSoldier->previous = t;
    root->previous = newSoldier;
    newSoldier->next = root;
    root = newSoldier;
  }
  
  return root;
}

Soldier *Insert_Back(Soldier *root, Soldier *newSoldier)
{
  Soldier *newItem = root;
  
  if(newItem == NULL)
  {
    newItem = newSoldier;
    newItem->next = newItem;
    newItem->previous = newItem;
  }
  else
  {
    
    // Adjust the new node next and previous link.
    newSoldier->next = newItem;
    newSoldier->previous = newItem->previous;
    
    // Adjust the old tail next link.
    newItem->previous->next = newSoldier;
    
    // Adjust the previous link of the head.
    newItem->previous = newSoldier;
  }
  
  
}
// Delete the current head of the list then return the new head.
Soldier *Delete_Front(Soldier *root)
{
  Soldier *newRoot = NULL;
  newRoot = root->next;
  newRoot->previous = root->previous;
  root->previous->next = newRoot;
  
  free(root);
  
  return newRoot;
}

// Delete the last item in the list.
void Delete_Back(Soldier *root)
{
  Soldier *lastNode = root->previous;
  
  lastNode->previous->next = root;
  root->previous = lastNode->previous;
  
  free(lastNode);
}

// Returns the new position where t will be since current node is deleted.
Soldier *Delete_Current_Node(Soldier *currentSoldier)
{
  Soldier *newPosition = NULL;
  // Link up the nodes from where they are being removed.
  currentSoldier->next->previous = currentSoldier->previous;
  currentSoldier->previous->next = currentSoldier->next;
  
  newPosition = currentSoldier->next;
  
  free(currentSoldier);
  
  return newPosition;
}

// Create a linked list of size n, creates each node and adds them.
Soldier *Create_Reverse_Circle(int n)
{
  int i;
  Soldier *root = NULL;
  for(i = 1; i <= n; i++)
  {
    root = Insert_Front(root, Create_Soldier(i));
  }
  
  return root;
}

int GetListSize(Soldier *root)
{
  int counter = 1;
  Soldier *t = root;
  
  while(t->next != root)
  {
    counter++;
    t = t->next;
  }
  
  //printf("List size:%d\n", counter);  
    
  return counter;
}

//Reverse the link list given the root node.
Soldier *Rearrange_Circle(Soldier *root)
{
  // there is no list.
  if(root == NULL)
  {
    printf("The list is empty, there is nothing to rearrange!");
    return NULL;
  }
  // there is a list, begin reversing.
  else
  {
    
    Soldier *t = root;
    Soldier *previous = root->previous, *next = NULL;
    int listSize = GetListSize(root);
    
    for(int i = 0; i < listSize; i++)
    {
      next = t->next;
      t->next = previous;
      t->previous = next;
      
      previous = t;
      t = next;
    }
    
    root = previous;
    return root;
  }
  
}

// Display the linked list in order from head to end.
void Display(Soldier *root)
{
  // There is no list so return.
  if(root == NULL)
  {
    printf("Error, head is null!");
    return;
  }

  Soldier *t = root;
  
  //printf("Sequence number (Next, previous):");
  while(t->next != root)
  {
    
    //printf("%d (N:%d, P:%d),", t->sequenceNumber, t->next->sequenceNumber, t->previous->sequenceNumber);
    printf("%d,", t->sequenceNumber);
    t = t->next;
  }
  
  printf("%d\n", t->sequenceNumber);
  //printf("%d (N:%d, P:%d)\n", t->sequenceNumber, t->next->sequenceNumber, t->previous->sequenceNumber);
  
}

// Deletes the Soldier nodes based on input skip interval.
int Kill(Soldier *root, int n, int k)
{
    // int n is our starting list size.
    int counter = n, skipInterval = k - 1, i;
    Soldier *t = root;
    
    while(counter > 1)
    {
      
      for(i = 0; i < skipInterval; i++)
      {
        t = t->next;
      }
      // Delete the current spot and then returns our new position.
      t = Delete_Current_Node(t);
      counter--;
    }
    //printf("%d", t->sequenceNumber);
    
    return (t->sequenceNumber);
}

int main(void)
{
  int survivingSoldier = 0, n, k; 
  Soldier* soldierList = NULL;
  
  printf("How many soldier are there? ");
  scanf("%d", &n);
  
  printf("What will be our skipping interval(k):");
  scanf("%d", &k);
  
  soldierList = Create_Reverse_Circle(n);
  printf("Reverse Order:");
  Display(soldierList);
  
  soldierList = Rearrange_Circle(soldierList);
  printf("Correct Order:");
  Display(soldierList);
  
  survivingSoldier = Kill(soldierList, n, k);
  printf("Surviving Soldier: %d\n", survivingSoldier);
  
  return 0;
}