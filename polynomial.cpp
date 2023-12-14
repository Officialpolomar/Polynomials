#include "polynomial.h"
#include <string>
using namespace std;

/*-----------------------------------------------------------------
   Converts the array of terms from the polyInput parameter
   into the linked list within the Polynomial object 
-------------------------------------------------------------------
*/


void Polynomial::stringToList(string* terms, int termNum, int currentTerm)
{
    Node* newNode = new Node;
    Node* nodePtr;
    string temp = "";
    int localCoefficient = 0;
    int indexOfExpoChar = 0;

  // constant term condition
    if (!isVariable(terms[currentTerm]))
    {
    // cout << "No X!!" << endl;
        for(int i = 0; i < terms[currentTerm].length(); i++)
        { 
            if(isdigit(terms[currentTerm][i]))
            {
                temp.push_back(terms[currentTerm][i]);
            } 
        }
    
        if(terms[currentTerm][0] == '-')
        {
            newNode->coefficient = stringToInt(temp) * -1;
        } 
        else 
        {
            newNode->coefficient = stringToInt(temp);
        }

        newNode->exponent = 0; 
    } 
    else
    {
    // cout << "Has X!!" << endl;
        int counter = 0;
        int j = 0;
        //checking coefficient value
        while(terms[currentTerm][j] != 'x')
        {
            if(isdigit(terms[currentTerm][j]))
            {
                temp.push_back(terms[currentTerm][j]);
            }

            j++;
        }
    
        //linear or exponent term condition
        for(int i = 0; i < terms[currentTerm].length(); i++)
        {
      
            if((terms[currentTerm][i] == 'x' || terms[currentTerm][i] == 'X')  && terms[currentTerm][i + 1] == '\0')
            {
                newNode->exponent = 1;
            } 
            else if ((terms[currentTerm][i] == 'x' || terms[currentTerm][i] == 'X') && terms[currentTerm][i + 1] == '^')
            {
                indexOfExpoChar = i + 1;
            }
        
        }

        if(terms[currentTerm][0] == '-')
        {
          newNode->coefficient = stringToInt(temp) * -1;

          if(newNode->coefficient == 0)
          {
              newNode->coefficient = -1;
          }

        } 
        else 
        {
            newNode->coefficient  = stringToInt(temp);

            if(newNode->coefficient == 0)
            {
                newNode->coefficient = 1;
            }

        }
    }

    temp.erase(0);

      //exponential term condition
  if (indexOfExpoChar > 0)
    {

      for (int i = indexOfExpoChar + 1; i < terms[currentTerm].length(); i++)
      {
        
        if (isdigit(terms[currentTerm][i]))
        {
          temp.push_back(terms[currentTerm][i]);
        }
        
      }
        //conditional if exponent is negative
        if (terms[currentTerm][indexOfExpoChar + 1] == '-')
        {
          newNode->exponent = stringToInt(temp) * -1;
        }
        else 
        {
          newNode->exponent = stringToInt(temp);
        }
      
    }

    newNode->next = nullptr;
    /*
    cout << "Term " << i + 1 << endl; 
    cout << "Ceofficient: " << newNode->coefficient << endl;
    cout << "Exponent: " << newNode->exponent << endl;
    */

      if ((!head && (newNode->coefficient != 0 || newNode->exponent != 0)) || (termNum == 1))
      {
          head = newNode;
          //Node added increase length by one
          length++;
      } 
      else if(head)
      {
          nodePtr = head;
    
          while (nodePtr->next)
          {
              nodePtr = nodePtr->next;
          }
          nodePtr->next = newNode;
          length++; 
      }

    if(currentTerm + 1 == termNum){
      delete [] terms;
      terms = nullptr;
      return;
    } 
    else 
    {
      stringToList(terms, termNum, currentTerm + 1);
    }

  

}



bool Polynomial::isdigit(char digit)
{

  if(digit == '0'){
    return true;
  }
  if(digit == '1'){
    return true;
  }
  if(digit == '2'){
    return true;
  }
  if(digit == '3'){
    return true;
  }
  if(digit == '4'){
    return true;
  }
  if(digit == '5'){
    return true;
  }
  if(digit == '6'){
    return true;
  }
  if(digit == '7'){
    return true;
  }
  if(digit == '8'){
    return true;
  }
  if(digit == '9'){
    return true;
  }

  return false;
  
}

int Polynomial::stringToInt(string playerNum)
{
   int num = 0;
   int l = playerNum.length();

   for(int i = 0; i < l; i++)
   {
      num = num * 10 + (int(playerNum[i]) - 48 ); 
   }
    
   return num;
}


bool Polynomial::isVariable(string termInput)
{

   for(int i = 0; i < termInput.length(); i++)
   {

     if(termInput[i] == 'x' || termInput[i] == 'X')
     {
      return true;
     }
    
   }

   return false;
}


void Polynomial::displayTerms() const
{
  int counter = 1;
  Node* nodePtr;
    
  if (!head)
  {
  cout << "List is empty";
  } 
  else 
  {
    nodePtr = head; 
    while (nodePtr)
    {  
      //for the first term
      if(counter == 1)
      { 
        if(nodePtr->exponent < 0 || nodePtr->exponent > 1)
          {
            
            if(nodePtr->coefficient < -1 || nodePtr->coefficient > 1)
            {
           cout << nodePtr->coefficient << "x^" << nodePtr->exponent;
            }
            else if(nodePtr->coefficient == 1)
            {
              cout << "x^" << nodePtr->exponent;
            }
            else if(nodePtr->coefficient == -1)
            {
               cout << "-x^" << nodePtr->exponent;
            }
            
          } 
        //exponent is equal to zero 
           if(nodePtr->exponent == 0)
          {
            cout << nodePtr->coefficient;
          } 
        //exponent is equal to one
           if(nodePtr->exponent == 1) 
          {
              
             if(nodePtr->coefficient < -1 || nodePtr->coefficient > 1)
               {
                 cout << nodePtr->coefficient << "x";
               }
               else if(nodePtr->coefficient == 1)
               {
                 cout << "x";
               }
               else if(nodePtr->coefficient == -1)
               {
                 cout << "-x^";
               }
          }  
      }
      
    //if coefficient is less than than -1 
      if(counter != 1 && nodePtr->coefficient < -1)
      {
        //exponent greater than one or negative
          if(nodePtr->exponent < 0 || nodePtr->exponent > 1)
          {
           cout << " - " << nodePtr->coefficient * -1 << "x^" << nodePtr->exponent;
          } 
        //exponent is equal to zero 
          else if(nodePtr->exponent == 0)
          {
            cout << " - " << nodePtr->coefficient * -1;
          } 
        //exponent is equal to one
          else if(nodePtr->exponent == 1) 
          {
             cout << " - " << nodePtr->coefficient * -1 << "x";
          }
      
      }
    // if coefficient is greater than one
      if(counter != 1 && nodePtr->coefficient > 1) 
      {
        //exponent greater than one or negative
          if(nodePtr->exponent < 0 || nodePtr->exponent > 1)
          {
           cout << " + " << nodePtr->coefficient << "x^" << nodePtr->exponent;
          } 
        //exponent is equal to zero 
          else if(nodePtr->exponent == 0)
          {
            cout << " + " << nodePtr->coefficient;
          } 
        //exponent is equal to one
          else if(nodePtr->exponent == 1) 
          {
             cout << " + " << nodePtr->coefficient << "x";
          }
  
      }
       // if coefficient is equal to one
      if(counter != 1 && nodePtr->coefficient == 1)
      {

        //exponent greater than one or negative
          if(nodePtr->exponent < 0 || nodePtr->exponent > 1)
          {
           cout << " + x^" << nodePtr->exponent;
          } 
        //exponent is equal to zero 
          else if(nodePtr->exponent == 0)
          {
            cout << " + " << nodePtr->coefficient;
          } 
        //exponent is equal to one
          else if(nodePtr->exponent == 1) 
          {
             cout << " + x";
          }

        
      }

      // if coefficient is equal to -
      if(counter != 1 && nodePtr->coefficient == -1)
      {
         //exponent greater than one or negative
           if(nodePtr->exponent < 0 || nodePtr->exponent > 1)
           {
            cout << " - x^" << nodePtr->exponent;
           } 
         //exponent is equal to zero 
           else if(nodePtr->exponent == 0)
           {
             cout << " - " << nodePtr->coefficient * -1;
           } 
         //exponent is equal to one
           else if(nodePtr->exponent == 1) 
           {
              cout << " - x";
           }


        
      }      
      /*
      //code do display whats in linked list
      cout <<"Term " << counter << endl;
      cout <<"Coefficient " << nodePtr->coefficient << endl;
      cout << "Exponent " << nodePtr->exponent << endl;
      cout << endl;
      */
      //move to next node
       nodePtr = nodePtr->next;
       counter++; 
    }
    
  }
  
}

int Polynomial::getCoefficient(int nodeNumber) const
{

  int counter = 0;
  Node* nodePtr;

     if (!head)
    {
   return -1;
    } 
    else 
    {
      nodePtr = head;
      while (nodePtr && counter < nodeNumber)
      {

        if(counter == nodeNumber - 1)
         {
         return nodePtr->coefficient;
         }
      
         nodePtr = nodePtr->next;
         counter++;
     }

  
    }
    return -2;
}

int Polynomial::getExponent(int nodeNumber) const
{

    int counter = 0;
    Node* nodePtr;

    if (!head)
    {
    return -1;
    } 
    else 
    {
      nodePtr = head;
      
      while (nodePtr && counter < nodeNumber)
      {
        
         if(counter == nodeNumber - 1)
         {
           return nodePtr->exponent;
         }

         nodePtr = nodePtr->next;
         counter++;
      }


     }
  
  return -2;
}

void Polynomial::appendNode(int coefficient, int exponent)
{

Node* transversePtr = nullptr;
Node* newerNode;
newerNode = new Node;

//assign values to new node
newerNode->coefficient = coefficient;
newerNode->exponent = exponent;
newerNode->next = nullptr;

  if (!head){
    head = newerNode;
    length++;
  } 
  else 
  {
    transversePtr = head;

    while (transversePtr->next)
     {

       transversePtr = transversePtr->next;
     }
       //Node added increase length by one
    transversePtr->next = newerNode;
       length++;

  }

  
}

int Polynomial::getLength() const{
  return length;
}

bool Polynomial::isEmpty() const{
  if (!head)
  {
   return true;
  } 
   return false; 
}
/*
Polynomial::~Polynomial(){

Node *nodePtr;
Node *nextNode;

nodePtr = head;

  while(nodePtr)
  {
     nextNode = nodePtr->next;
    
    delete nodePtr;
    
    nodePtr = nextNode;
  }
  nodePtr = nullptr;
  nextNode = nullptr;
  
}
*/



void Polynomial::operator=(const Polynomial& p)
{
  Node* temPtr; // to iterate through the list 
  Node* current; // to build new list
  length = p.length;
  
  head = new Node;
  temPtr = p.head;
  head->coefficient = temPtr->coefficient;
  head->exponent = temPtr->exponent;
  current = head;

  temPtr = temPtr->next;
  
  
  while(temPtr){
  current->next = new Node;
  current = current->next;
  current->coefficient = temPtr->coefficient;
  current->exponent = temPtr->exponent;
  current->next = nullptr;

   temPtr = temPtr->next;
  }
  
}

void Polynomial::deleteList(){
  Node* nodePtr;
  Node* ptrHolder;

  if(!head)
  {
    return;
  } 
  else 
  {
    nodePtr = head;
    
    while (nodePtr)
    {
      ptrHolder = nodePtr->next;
      delete nodePtr;
      nodePtr = ptrHolder;
    }
    
    
  }

  head = nullptr;
  nodePtr = nullptr;
  ptrHolder = nullptr;

  length = 0;
   
}
