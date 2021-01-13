#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *next;

}Node;



typedef struct queue
{
  struct node *front;
  struct node *back;
  
}Queue;

void Init(Queue *queue)
{
  queue->front = NULL;
  queue->back = NULL;
}

Node *CreateNode()
{
  Node *temp = malloc(sizeof(Node));
  temp->data = 0;
  temp->next = NULL;
  
  return temp;
}

int Front(Queue *queue)
{  
  if(queue->front == NULL)
    return -1;
  
  return queue->front->data;
}

int Back(Queue *queue)
{
  if(queue->back == NULL)
    return -1;
  
  return(queue->back->data);
}

int IsEmpty(Queue *queue)
{
  return (queue->front == NULL && queue->back == NULL);
}

void Enqueue(Queue *queue, int data)
{
  Node *temp = CreateNode();
  
  temp->data = data;
  

  if(queue->back == NULL)
  {
    queue->front = temp;
    queue->back = temp;
    return;
  }  
  
  queue->back->next = temp; 
  queue->back = temp;
  queue->back->next = NULL;
}

void Dequeue(Queue *queue)
{
  
  Node *temp = queue->front;
  free(temp);
  queue->front = queue->front->next;
  
  if(queue->front == NULL)
    queue->back = NULL;
}


int main(void)
{
  int queueSize = 5, i;
  Queue *myLine = malloc(sizeof(Queue));
  Init(myLine);
  
  // Populate the queue.
  for(i = 0; i < queueSize; i++)
  {
      Enqueue(myLine, (i + 1));
  }
  printf("The data at the front of the queue is: %d\n", Front(myLine));
  printf("The data at the back of the queue is: %d\n", Back(myLine));
  
  Dequeue(myLine);
  printf("Front is now: %d\n", Front(myLine));
  
  Enqueue(myLine, 10);
  printf("The data at the back of the queue now is: %d\n", Back(myLine));
  
  while(!IsEmpty(myLine))
  {
    Dequeue(myLine);
  }
  
  if(IsEmpty(myLine))
    printf("The queue is now empty!\n");
  else
    printf("There are still items within the queue.\n");
  
  
  return 0;
}  