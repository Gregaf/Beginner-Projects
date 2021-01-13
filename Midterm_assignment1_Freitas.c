/* COP 3502C Midterm Assignment One This program is written by: Gregory Freitas */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50
#define EMPTY -1

// CHAR STACK (START)
struct charStack {

    char items[SIZE];
    char top;

};

char Peek_Char(struct charStack *stackPtr)
{
  return stackPtr->items[stackPtr->top];
}

// Sets the int Stack top to -1 just to intialize it.
void Initialize_Char(struct charStack *stackPtr) 
{
     stackPtr->top = -1;
}

// Returns true if the stack pointed to by stackPtr is empty.
int Empty_Char(struct charStack* stackPtr) 
{
    return (stackPtr->top == -1);
}

// Returns true if the stack pointed to by stackPtr is full.
int Full_Char(struct charStack *stackPtr) 
{
    return (stackPtr->top == SIZE - 1);
}

// Unable to push if returned 0, able if returned 1.
int Push_Char(struct charStack *stackPtr, char value) 
{

    // Check if the stack is full.
    if (Full_Char(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}


char Pop_Char(struct charStack *stackPtr) 
{
    char returnValue;

    // Check the case that the stack is empty.
    if (Empty_Char(stackPtr))
        return EMPTY;

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    returnValue = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return returnValue;
}
// CHAR STACK (END)


// INTERGER STACK (START)
struct intStack {

    int items[SIZE];
    int top;

};

// Sets the int Stack top to -1 just to intialize it.
void Initialize_Int(struct intStack *stackPtr) 
{
     stackPtr->top = -1;
}

// Returns true if the stack pointed to by stackPtr is empty.
int Empty_Int(struct intStack* stackPtr) 
{
    return (stackPtr->top == -1);
}

// Returns true if the stack pointed to by stackPtr is full.
int Full_Int(struct intStack *stackPtr) 
{
    return (stackPtr->top == SIZE - 1);
}

// Unable to push if returned 0, able if returned 1.
int Push_Int(struct intStack *stackPtr, int value) 
{

    // Check if the stack is full.
    if (Full_Int(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns -1 if the stack is empty
int Pop_Int(struct intStack *stackPtr) 
{
    int returnValue;

    // Check the case that the stack is empty.
    if (Empty_Int(stackPtr))
        return EMPTY;

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    returnValue = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return returnValue;
}
// INTERGER STACK (END)


// Display a menu, accept input or exit.
char *Menu()
{
  char *infix = NULL;
  char myChar;
  printf("Press 'e' to enter infix or 'x' to exit the program:");
  scanf("%c%*c", &myChar);
  
  if(myChar == 'e')
  {
    // Dynamically allocate memory for an infix of up to 50 characters.
    infix = (char *) malloc(SIZE * sizeof(char));
    fgets(infix, SIZE, stdin);
    
    return infix;
  }
  else if(myChar == 'x')
  {
    // Dynamically allocate memory for "exit".
    infix =(char *) malloc(5 * sizeof(char));
    infix = "exit";
    
    printf("Exiting...\n");
    return infix;
  }
  else
  {
    //Invalid Input.
    return "exit";
  }
  
}

// Take the infix to check if the paranthesis are balanced.
int IsBalancedParenthesis(char *infix)
{
  int i, infixLength = strlen(infix);
  
  struct charStack myStack;
  Initialize_Char(&myStack);
  
  // Check infix from left to right.
  for(i = 0; i < infixLength; i++)
  {
    // '(' encountered push it to the stack.
    if(infix[i] == '(')
      Push_Char(&myStack, infix[i]);
    // ')' encountered then Pop the stack.
    else if(infix[i] == ')')
    {
       // If we run into a closing parentheses and the stack is empty then its imbalanced. Return false.
       if(Empty_Char(&myStack) == 1)
         return 0;
       
       Pop_Char(&myStack);
       
    }
    else
    {
      // Parenthese is not read this iteration. Want to do something?
    }
  }
  
  // If the stack is empty then its balanced. return true otherwise return false
  if(Empty_Char(&myStack) == 1)
    return 1;
  else
    return 0;
}

// Check for operator or operand, return 1 for operator and 0 for operand.
int IsOperator(char c)
{
  if(c == '^' || c == '*' || c == '/' || c == '%' || c == '+' || c == '-')
    return 1;
  else
    return 0;
}

// return the operator priority.
int GetOperatorPriority(char c)
{
  if(c == '^')
  {
    // ^ has the highest priority.
    return 3;
  }
  else if (c == '*' || c == '/' || c == '%')
  {
    // * / % has next highest priority.
    return 2;
  }
  else if(c == '+' || c == '-')
  {
    // + or -  has lowest priority.
    return 1;
  }
  else
  {
    // It is not an operator so 0 priority is returned.
    return 0;
  }

}

// convert single digit to int and return it.
int ConvertToInt(char c)
{
  int digit =  c - '0';
  
  return digit;
}

// Check if the character is a digit.
int IsDigit(char c)
{
  if(c >= '0' && c <= '9')
    return 1;
  else
    return 0;
}


// Takes two operands and an operator and returns the resulting calculation.
int Calculate(int a, int b, char op)
{ 
  int result = 0;
  
  switch(op)
  {
    case '+':
    result = (a + b);
    return result;
    
    case '-':
    result = (b - a);
    return result;
    
    case '*':
    result = (a * b);
    return result;
    
    case '/':
    result = (b / a);
    return result;
    
    case '%':
    result = (b % a);
    return result;
    
    case '^':
    // result = result * base, perform the operation until the exponent has been decreased to 0. (b^a)
    result = 1;
    while(a != 0)
    {
      result *= b;
      a--;
    };
    return result;
      
  }
  
}

// Evaluate the equation given in postfix form.
void Evaluate(char *postfix)
{
  int postfixLength = strlen(postfix);
  int i, currentElement = 0, a = 0, b = 0, currentEval = 0, result = 0, digits = 12;
  struct intStack myStack;
  Initialize_Int(&myStack);
  
  // Read the postfix from left to right.
  for(i = 0; i < postfixLength; i++)
  {
    // Ignore spaces.
    if(postfix[i] == ' ')
      continue;
    
    // If the character is an Operand and a digit convert it to an int then push it to the evaluation stack.
    if(IsOperator(postfix[i]) == 0 && IsDigit(postfix[i]) == 1)
    {  
      // If it is multidigit...
      if(IsDigit(postfix[i]) && IsDigit(postfix[i + 1]))
      {
        char buffer[digits];
        currentElement = 0;
        
        // Keep storing the digits to the buffer.
        while(IsDigit(postfix[i]))
        {
          buffer[currentElement++] = postfix[i];
          i++;
        }
        // Add the null terminator for the buffer.
        buffer[currentElement++] = '\0';
        
        // Use atoi to convert string to integer and then push it to the stack.
        Push_Int(&myStack, atoi(buffer));    
      }
      // It is single digit, so convert to int and push it to the stack.
      else
        Push_Int(&myStack, ConvertToInt(postfix[i]));
    }
    // Otherwise the character is an Operator...
    else
    {
      // Pop and save two operands in the stack.
      a = Pop_Int(&myStack);
      b = Pop_Int(&myStack);
      
      // Evaulate those operands with the operator, then push the evaluation to the stack.
      currentEval = Calculate(a, b, postfix[i]);
      
      //printf("a:%d b:%d eval:%d\n", a, b, currentEval);
      Push_Int(&myStack, currentEval);  
    }    
    
  }
  
  result = Pop_Int(&myStack);
  
  printf("Result: %d\n", result);
}


// Convert infix to postfix
char *ConvertToPostfix(char *infix)
{
  char *postfix = (char *) malloc(SIZE * sizeof(char));
  char currentOperator;
  int i, currentElement, infixLength = strlen(infix);
  
  struct charStack myStack;
  Initialize_Char(&myStack);
  
  // Read the infix from left to right.
  for(i = 0, currentElement = 0; i < infixLength; i++)
  {  
    // Dont add new lines or spaces from the infix to the postfix.
    if(infix[i] == '\n' || infix[i] == ' ')
      continue;
  
    
    // If the character is an operand and a digit...
    if(IsOperator(infix[i]) == 0 && IsDigit(infix[i]) == 1)
    {     
      // Multiple Digits.
      if(IsDigit(infix[i]) && IsDigit(infix[i + 1]))
      {
        
        postfix[currentElement++] = infix[i];
      }
      // Single Digits.
      else
      {
        postfix[currentElement++] = infix[i];
        postfix[currentElement++] = ' ';
      }
      
    }
    // If an '(' is found push it to the stack.
    else if(infix[i] == '(')
    {
      Push_Char(&myStack, infix[i]);
    }
    // If we encounter a closed paraenthese then Pop until a open paraenthese is found.
    else if(infix[i] == ')')
    {
      // Keep Popping the stack and adding it to postfix until we find an '('.
      while(Peek_Char(&myStack) != '(')
      {
        postfix[currentElement++] = Pop_Char(&myStack);
        postfix[currentElement++] = ' ';
                   
      }
      // Once the while loop stops we found a '(' so we Pop it out of the stack.
      Pop_Char(&myStack);
       
    }
    // Otherwise if the character is an operator...
    else if(IsOperator(infix[i]) == 1)
    {
      currentOperator = infix[i];
      
      // If my stack is empty push the current Operator to the stack.
      if(Empty_Char(&myStack) == 1)
      {
        Push_Char(&myStack, currentOperator);
      }
      // If the priority of the current operator is greater than the operator at the top of the stack Push my current operator to the stack.
      else if(GetOperatorPriority(currentOperator) > GetOperatorPriority(Peek_Char(&myStack)))
      {
        Push_Char(&myStack, currentOperator);
      }
      // If the priority of the current operator is equal to or less than the operator at the top of the stack then Pop the stack...
      // ...and append the char to the postfix and then continue Poping till it is the greatest priority and then push it to the stack.
      else if(GetOperatorPriority(currentOperator) <= GetOperatorPriority(Peek_Char(&myStack)))
      {
        while(GetOperatorPriority(currentOperator) <= GetOperatorPriority(Peek_Char(&myStack)))
        {
          postfix[currentElement++] = Pop_Char(&myStack);
          postfix[currentElement++] = ' ';
        }
        
        Push_Char(&myStack, currentOperator);
      }
      
    }
    // Unkown character encountered.
    else
    {
      //printf("Invalid Character.");
    }
    
  }
  
  // As long as the stack isn't empty pop and append the characters to the postfix.
  while(Empty_Char(&myStack) != 1)
  {
    postfix[currentElement++] = Pop_Char(&myStack);
    postfix[currentElement++] = ' ';
  }
  
  // Assign a null character to the end of the postfix.
  postfix[currentElement++] = '\0';
  
  return postfix;  
}


int main(void)
{
  char *postfix = NULL;
  char *str = NULL;
  
  while(strcmp(str = Menu(), "exit") != 0)
  {
      
     if(IsBalancedParenthesis(str))
     {
       printf("Parenthesis balanced.\n");
       postfix = ConvertToPostfix(str);
       
       printf("Postfix:%s\n", postfix);
       Evaluate(postfix);
     }
     else
     {
       printf("Parenthesis imbalanced.\n");
       break;
     } 
      
     free(postfix);
     free(str);  
  }  

  return 0;
}