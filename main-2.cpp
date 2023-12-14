#include <iostream>
#include "polynomial.h"
#include "polynomial.cpp"
#include <string>
using namespace std;

//10 Dec, 2023  fix up input validation for polynomial input 
struct Node {
  int coefficient;
  int exponent;
  Node* next;
};

Polynomial Add(const Polynomial, const Polynomial);
Polynomial Multiply(const Polynomial, const Polynomial);
void eraseSpace(string&);
void parsePolyInput(string, int, string[]);
void isNumberValid(string&, int, int);
int stringToIntMain(string);
int getNumberOfOperators(string);
int nextHighest(int, Node*, int);
bool spacesCheck(string);
bool IsInputValid(string*, int);
bool IsVariable(string);
bool isdigit(char);
bool HasExponent(string);
int  LocateChar(string, char);


int main() 
{
    const int MAX_POLY = 11;

    int polyNum;
    string* termArrayPtr;
    string tempPolyNum;
    string polynomialInput;
    Polynomial polyArray[MAX_POLY];
    Polynomial sum;
    Polynomial product;
    Polynomial temp;
    
  
    
    cout << "\nWelcome!\n\n This program gives the product and sum of anywhere between 2 and 11 polynomials.\n";
    cout << " To end the program, input zero when asked for amount of polynomials desired.\n";
    cout << " Other Limitions: cannot multiply polynomials with a variable by zero(will crash program).\n";
    cout << "\nHow many polynomals do you want the sum and product of? "; 
    getline(cin, tempPolyNum);

    if(tempPolyNum != "0")
    {
        isNumberValid(tempPolyNum, 2, 11);
    }
    
    polyNum = stringToIntMain(tempPolyNum);
    cout << endl;
    
    while (polyNum != 0)
    {

      for (int i = 0; i < polyNum; i++)
      {
          cout <<"Please input polynomial " << i + 1 << " --> ";
          getline(cin, polynomialInput);
          eraseSpace(polynomialInput);
          int numTerms = getNumberOfOperators(polynomialInput);
          termArrayPtr = new string[numTerms];

          if (numTerms == 1)
          {
              termArrayPtr[0] = polynomialInput;
          } 
          else 
          {
              parsePolyInput(polynomialInput, numTerms, termArrayPtr);
          }
          
          while(!IsInputValid(termArrayPtr, numTerms))
          {
              cout << "\nInput polynomial " << i + 1 << " again\n--> ";
              getline(cin, polynomialInput);
              eraseSpace(polynomialInput);
              numTerms = getNumberOfOperators(polynomialInput);
            
              if (numTerms == 1)
              {
                termArrayPtr[0] = polynomialInput;
              } 
              else 
              {
                parsePolyInput(polynomialInput, numTerms, termArrayPtr);
              }
            
           }

          polyArray[i].stringToList(termArrayPtr, numTerms, 0);
    }
    
      for (int i = 0; i < polyNum; i++)
      {
          if (i == 0)
          {
              temp = Add(polyArray[i], polyArray[i+1]);
              sum = temp;
              i = 1;
              continue;
          }
      
          sum = Add(temp, polyArray[i]);
          temp = sum;
      }

      cout << "\nSum = ";
    
      for (int j = 0; j < polyNum; j++)
      {
          cout << "(";
          polyArray[j].displayTerms();
          cout << ")";
      
          if (j != polyNum - 1)
          {
              cout << " + ";
          }

      }

      cout << endl;
      cout << "    = ";
      sum.displayTerms();
      temp.deleteList();
    
    for (int i = 0; i < polyNum; i++)
    {
        if (i == 0)
        {
            temp = Multiply(polyArray[i], polyArray[i+1]);
            product = temp;
            i = 1;
            continue;
        }

        product = Multiply(temp, polyArray[i]);
        temp = product;
    }

      cout << "\n\n\nProduct = ";

      for (int j = 0; j < polyNum; j++)
      {
          cout << "(";
          polyArray[j].displayTerms(); 
          cout << ")";
        
          if (j != polyNum - 1)
          {
              cout << " * ";
          }

      }
      
      cout << endl;
      cout << "        = ";
      product.displayTerms();
      cout << "\n\n---------------------------------------------------" << endl;

      //delete linked list in polynomials 
      for (int i = 0; i < polyNum; i++)
      {
        polyArray[i].deleteList();
      }
      
      product.deleteList();
      sum.deleteList();
      temp.deleteList();

      cout << "\nHow many polynomals do you want the sum and product of? ";
      getline(cin, tempPolyNum);

      if(tempPolyNum != "0")
      {
          isNumberValid(tempPolyNum, 2, 11);
      }
        
      polyNum = stringToIntMain(tempPolyNum);
      cout << endl;
    }

    cout << "\nProgram has ended, good day.\n";
}


void eraseSpace(string &polynomialInput)
{
    int spaceCounter = 0;

    for (int i = 0; i < polynomialInput.length(); i++)
  {
    while (polynomialInput[i] == ' ')
    {
      polynomialInput.erase(i,1);
    }      
  }
}

int getNumberOfOperators(string polyNum)
{

 int operatorCount = 0;

   for (int i = 0; i < polyNum.length(); i++)
   {

     if ((polyNum[i] == '+' || polyNum[i] == '-') && i != 0 && !(polyNum[i-1] == '^' && polyNum[i] == '-'))
     {
       operatorCount++;
     }
     
   }

  return operatorCount + 1;
}

void parsePolyInput(string rawInput, int terms, string* termArray)
{
    int operatorLocation = 0;
    int operatorCounter = 0; 
    int j = 0;
     

    for (int i = 0; i < rawInput.length(); i++)
    {
        j++;
      //if there is a plus or minus and it isn't the first character in string, use as marker to split term into polynomial array
      if ((rawInput[i] == '+' || rawInput[i] == '-') && i != 0 && !(rawInput[i-1] == '^' && rawInput[i] == '-'))
      {
          termArray[operatorCounter] = rawInput.substr(operatorLocation, j-1);
          operatorCounter++;
          operatorLocation = i;
          j = 1;
      } 

      if (operatorCounter == terms - 1)
      {
          termArray[operatorCounter] = rawInput.substr(operatorLocation, rawInput.length() - (i - 1));
          break;
      } 
    }

  
  
  
}


void isNumberValid(string& size, int lowerBound, int upperBound)
{
    while ((stringToIntMain(size) < lowerBound || stringToIntMain(size) > upperBound) || (!spacesCheck(size)) || size.find('.') != -1 )
  {
    if (size.find('.') != -1)
    {

      cout << "Input cannot be a decimal, try again. " << endl;
      getline(cin, size);
      continue;
    }
    
    if (!spacesCheck(size))
    {
      cout << "Input cannot have a space. Try again. " << endl;
      getline(cin, size);
      continue;
    }


    if (stringToIntMain(size) < lowerBound || stringToIntMain(size) > upperBound)
    {
      cout << "The input was not a number between " << lowerBound << " and " << upperBound << " try again." << endl;
      getline(cin, size);
      continue;
    }

  }

  
}

int stringToIntMain(string playerNum)
{

   int num = 0;
   int l = playerNum.length();

    if(playerNum[0] == ':' || playerNum[0] == ';')
    {
        return -1;
    }

    for (int i = 0; i < l; i++)
    {
        num = num * 10 + (int(playerNum[i]) - 48 ); 
    }
    
    return num;
}


bool spacesCheck(string playerName)
{

  for (int i = 0; i < playerName.length(); i++)
  {
    if (playerName[i] == ' ')
    {
    return false;
    }
  
  }

  return true;
}

Polynomial Add(const Polynomial poly1, const Polynomial poly2)
{
  int additionBoundary = 1;
  int pushBy = 0;
  bool isRemainer = false;
  int counter = 1;
   
  
  Polynomial polySum;
 
   if (poly1.isEmpty())
   {
     polySum = poly2;
     return polySum;
   }
  
  if (poly2.isEmpty())
   {
     polySum = poly1;
      return polySum;
   }

  if (poly2.isEmpty() && poly1.isEmpty())
  {
      return polySum;
  }
    

   if (poly1.getLength() <= poly2.getLength())
   {
  
    for (int i = 1; i <= poly2.getLength(); i++)
    {
       
        if (pushBy > 0)
        {
          additionBoundary += pushBy;
          pushBy = 0;
        }
      
        for (int k = additionBoundary; k <= poly1.getLength(); k++)
        {
            
             //condition if exponent of poly2 is greater then poly1
             if (poly2.getExponent(i) > poly1.getExponent(k))
             {
              
               counter++;
               isRemainer = false;
          polySum.appendNode(poly2.getCoefficient(i),poly2.getExponent(i));
               break;
             }
             
             //conditions if exponent of poly2 is less then poly1
             if (poly2.getExponent(i) < poly1.getExponent(k)) 
             {
              
               
               isRemainer = true;
               polySum.appendNode(poly1.getCoefficient(k),poly1.getExponent(k));
               pushBy++;
               continue; 
             }
             //conditions if exponents are equal 
            
             if (poly2.getExponent(i) == poly1.getExponent(k))
             {
               
               counter++;
               isRemainer = true;
               polySum.appendNode(poly1.getCoefficient(k) + poly2.getCoefficient(i), poly1.getExponent(k));
               additionBoundary++;
              break;
               
             }    
          
        }
     
    }
     //adding remaining terms after for loop if finished
     //terms for inner for loop poly 
    if (additionBoundary <= poly1.getLength() && (!isRemainer || (isRemainer && counter > poly2.getLength())))
    {
       while (additionBoundary <= poly1.getLength())
       {
          
         polySum.appendNode(poly1.getCoefficient(additionBoundary),poly1.getExponent(additionBoundary));
          additionBoundary++;
       }   
    }
     //terms for outer for loop poly 
     if (isRemainer)
     {  
       while (counter <= poly2.getLength())
        {
           
           polySum.appendNode(poly2.getCoefficient(counter),poly2.getExponent(counter));
           counter++;
        }   
     }
      
} 
else 
{
      for (int i = 1; i <= poly1.getLength(); i++)
        {
           
           
            if(pushBy > 0){
              additionBoundary += pushBy;
              pushBy = 0;
            }
           

            for(int k = additionBoundary; k <= poly2.getLength(); k++)
            {

                 //condition if exponent of poly2 is greater then poly1
                 if (poly1.getExponent(i) > poly2.getExponent(k))
                 {
                   
                   isRemainer = false;
                   counter++;
              polySum.appendNode(poly1.getCoefficient(i),poly1.getExponent(i));
                   break;
                 }

                 //conditions if exponent of poly2 is less then poly1
                 if (poly1.getExponent(i) < poly2.getExponent(k)) 
                 {
                  
                   isRemainer = true;
                   polySum.appendNode(poly2.getCoefficient(k),poly2.getExponent(k));
                   pushBy++;
                   continue; 
                 }
                 //conditions if exponents are equal 

                 if(poly1.getExponent(i) == poly2.getExponent(k))
                 {
                   
                   isRemainer = true;
                   counter++;
                  polySum.appendNode(poly2.getCoefficient(k) + poly1.getCoefficient(i), poly2.getExponent(k));
                  additionBoundary++;
                  break;

                 }    

            }

        }
     //adding remaining terms after for loop if finished
          //terms for inner for loop poly 
        if (additionBoundary <= poly2.getLength() && (!isRemainer || (isRemainer && counter > poly1.getLength())))
        {
           while (additionBoundary <= poly2.getLength())
           {
              
              polySum.appendNode(poly2.getCoefficient(additionBoundary), poly2.getExponent(additionBoundary));
              additionBoundary++;
           }   
        }
          //terms for outer for loop poly 
         if(isRemainer){
           while (counter <= poly1.getLength())
            {
              
               polySum.appendNode(poly1.getCoefficient(counter), poly1.getExponent( counter));
               counter++;
            }   
         }

     
   }
     
   

  return polySum; 

   
}

Polynomial Multiply(const Polynomial poly3, const Polynomial poly4)
{
  int highestPower = 0;
  int counter = 0;
  int expoCheck;
  Polynomial polyProduct;
  
  Node* tempTermArray = new Node[poly3.getLength() * poly4.getLength()];
  Node*  finalProduct = new Node[poly3.getLength() * poly4.getLength()];

  //making sure all coefficients in finalProduct are set to zero
      for(int i = 0; i < poly3.getLength() * poly4.getLength(); i++)
      {
        finalProduct[i].coefficient = 0; 
      }

  
  //multiply every term by every term and put in TempArray
    for(int i = 0; i < poly3.getLength(); i++)
    {
        for(int j = 0; j < poly4.getLength(); j++)
        {
            tempTermArray[counter].coefficient = poly3.getCoefficient(i+1) * poly4.getCoefficient(j+1);
            tempTermArray[counter].exponent = poly3.getExponent(i+1) + poly4.getExponent(j+1);
            counter++;
        }
    }
     

    //grouping like terms together to get final polynomial.
    //initailize first term into final product array
    int highestExpo = tempTermArray[0].exponent;
  
for (int j = 0; j < counter; j++)
{
      for (int i = 0; i < counter; i++)
      {
        if (tempTermArray[i].exponent == highestExpo)
        {
          finalProduct[j].exponent = tempTermArray[i].exponent;
          finalProduct[j].coefficient += tempTermArray[i].coefficient;
        }   
        
      } 
      //find next highest exponent
       expoCheck = highestExpo;
       highestExpo = nextHighest(highestExpo, tempTermArray, counter); 
    
      if (expoCheck == highestExpo)
      {
        break;
      }
    
}
  
  
/*
//code to print out what is in node array or polynomial
   for (int k = 0; k < poly3.getLength() * poly4.getLength(); k++)
   {
      cout << "\nTerm " << k + 1 << endl;
      cout << "Coefficient " << finalProduct[k].coefficient << "and Exponent " << finalProduct[k].exponent << endl;
   }
*/



  //input finalProduct into PolynomialProduct which will be returned
   for (int i = 0; i < counter; i++)
   {
     if (!(finalProduct[i].coefficient == 0 && finalProduct[i].exponent != 0))
     {
        polyProduct.appendNode(finalProduct[i].coefficient, finalProduct[i].exponent);
     }
   }

   delete [] finalProduct;
   delete [] tempTermArray;
   finalProduct = nullptr;
   tempTermArray = nullptr;
    
   return polyProduct;
}


int nextHighest(int highestNum, Node* nodeList, int listLength)
{
  


  int difference = highestNum;
  int num;
  int tempVal;
  int next_Highest_Below_Zero = -10000;
  
   if (highestNum == 1)
   {
      return 0;
   }

  
if(highestNum > 0){

    for (int i = 0; i < listLength; i++)
    {
      
      
      if (nodeList[i].exponent < highestNum && highestNum - nodeList[i].exponent < difference)
      {
          difference = highestNum - nodeList[i].exponent;
          num = nodeList[i].exponent; 
      }


    }
  
} 
else 
{
  
  
  for (int j = 0; j < listLength; j++)
    {

      if (nodeList[j].exponent < highestNum)
       {
          tempVal = difference + nodeList[j].exponent;

          if (tempVal > next_Highest_Below_Zero)
         {
           next_Highest_Below_Zero = nodeList[j].exponent;
         }
    
      }

    
   }

    num = next_Highest_Below_Zero;
  
}

  return num;

}

bool IsVariable(string termInput)
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
  

bool isDigit(char digit)
{
    if(digit >= 48 && digit <= 57)
    {
        return true;
    }

    return false;
  }

bool HasExponent(string poly_input)
{
  for (int i = 0; i < poly_input.size(); i++)
  {
      if(poly_input[i] == '^')
      {
          return true; 
      }
 
  }
  
  return false;
  
}
  

bool IsInputValid(string *poly_input, int number_of_terms)
{
    bool variable_used = false;
    int loop_start_number = 0;
    int current_exponent_value = 0;
    int temp_exponent_value = 0;
    int number_of_digits = 0;
    int carrot_location = 0;
    int minus_location = 0;
    
    for(int j = 0; j < number_of_terms; j++)
    {
        if(!IsVariable(poly_input[j]))
        {
            current_exponent_value = 0; // power of term

            //Check to see if the first digit is negative sign. If so, continue to next character
            //If the first char is not a negative since, then it must start with a digit or x. If not, return false.     
            if(poly_input[j][0] == '-')
            {
                loop_start_number++;
            }
            else if(poly_input[j][0] != '-' && !isDigit(poly_input[j][0]) && j == 0)
            {
                cout << "\n- INVALID INPUT " << endl;
                cout << "- First digit is not a negative sign, digit, or the variable x\n" << endl;
                return false;
            }
            else if(poly_input[j][0] != '-' && poly_input[j][0] != '+' && !isDigit(poly_input[j][0]) && j > 0)
            {
                cout << "\n- INVALID INPUT " << endl;
                cout << "- terms that are not first must start with a (-) or (+) sign\n" << endl;
                return false;
            }

            //if a (-) or (+) end the polynomial then return false 
            if(!isDigit(poly_input[j][0]) && poly_input[j].size() == 1)
            {
                cout << "(+) or (-) cannot end the polynomial\n";
                return false;
            }

            //if the first digit of number starts with a zero followed by a non-zero number
            if(poly_input[j][loop_start_number] == '0' && loop_start_number + 1 != poly_input[j].size())
            {
                cout << "\n- INVALID INPUT " << endl;
                cout << "- cannot input a zero and follow up with another digit\n" << endl;
                return false;
            }
          
            for(int i = loop_start_number; i < poly_input[j].size(); i++)
            {
                if(!isDigit(poly_input[j][i]))
                {

                    if(poly_input[j][i] != '+')
                  {
                      cout << "INVALID INPUT" << endl;
                      cout << "\n- Number has been interupted by a another chararacter which is not a digit\n" << endl;
                      return false; 
                  }

                }
                else
                {
                    number_of_digits++;
                }

                //if number of digits is over ten return false
                if(number_of_digits > 10)
                {
                    cout << "\nINVALID INPUT" << endl;
                    cout << "- Coefficent cannot be over 10 digits(outside Integer range)\n" << endl;
                    return false;
                }
            }

            loop_start_number = 0;
        } 
        else if (IsVariable(poly_input[j]) && !HasExponent(poly_input[j]))
        {
            current_exponent_value = 1;// power of exponent with variable

            //if first char is the negative sign then begin loop at next index
            if(poly_input[j][0] == '-')
            {
              loop_start_number++;
            }
          
          //If neither a negative sign, digit, or x starts the term there is an error
          if(poly_input[j][0] != '-' && 
          !isDigit(poly_input[j][0]) && 
            poly_input[j][0] != 'x' && 
            poly_input[j][0] != 'X' && 
            j == 0)
          {
              cout << "\n- INVALID INPUT " << endl;
              cout << "- X must be first when digit and negative sign are absent\n" << endl;
              return false;
          }
          else if(poly_input[j][0] != '-' && 
                  poly_input[j][0] != '+' && 
              !isDigit(poly_input[j][0]) && 
                  poly_input[j][0] != 'x' && 
                  poly_input[j][0] != 'X' && 
                  j > 0)
          {
              cout << "\n- INVALID INPUT " << endl;
              cout << "- terms that are not first must start with a (-) or (+) sign\n" << endl;
              return false;
          }
          
          //If the variable is not at the end of the term return false
          if(poly_input[j][poly_input[j].size() - 1] != 'x' && poly_input[j][poly_input[j].size() - 1] != 'X' )
          {
            cout << "\n- INVALID INPUT " << endl;
            cout << "- X variable must be last char in term when at power of one\n" << endl;
            return false;
          }

          
          //if the first digit of number starts with a zero followed by a non-zero number
          if(poly_input[j][loop_start_number] == '0' && loop_start_number + 1 != poly_input[j].size())
          {
            cout << "\n- INVALID INPUT " << endl;
            cout << "- cannot input a zero and follow up with another digit\n" << endl;
            return false;
          }
          
          for (int i = loop_start_number; i < poly_input[j].size(); i++)
          {
              //if character is not a digit or x variable return false
              if (!isDigit(poly_input[j][i]))
              {
                  if (poly_input[j][i] != 'x' && poly_input[j][i] != 'X') 
                  {
                      
                      cout << "INVALID INPUT" << endl;
                      cout << "\n- Number has been interupted by a another chararacter which is not a digit or variable x\n" << endl;
                      return false; 
                  }
              }
              else 
              {
                number_of_digits++;
              }

              //if number of digits is over ten return false
              if(number_of_digits > 10)
              {
                  cout << "\nINVALID INPUT" << endl;
                  cout << "- Coefficent cannot be over 10 digits(outside Integer range)\n" << endl;
                  return false;
              }
            
              
          } //outside for loop 
              number_of_digits = 0;
              loop_start_number = 0;
          
            
        }
        else if (IsVariable(poly_input[j]) && HasExponent(poly_input[j]))
        {

            // If first char is the negative sign then look at the next index in future if-statements
            if (poly_input[j][0] == '-')
            {
                loop_start_number++;
            }
            // If neither a negative sign, digit, or x starts the term there is an error
            else if (poly_input[j][0] != '-' && 
                    !isDigit(poly_input[j][0]) && 
                    poly_input[j][0] != 'x' && 
                    poly_input[j][0] != 'X' && 
                    j == 0)
            {
                cout << "\n- INVALID INPUT " << endl;
                cout << "First term of polynomial must start with a minus sign, digit, or x variable\n" << endl;
                return false;
            }
            // If there is not a plus or minus to connect terms return false
            else if (poly_input[j][0] != '-' && 
                    poly_input[j][0] != '+' && 
                    j > 0)
            {
                cout << "\n- INVALID INPUT " << endl;
                cout << "- terms that are not first must start with a (-) or (+) sign\n" << endl;
                return false;
            }
            
            // If not in the correct format for an postive or negative exponent return false
            if (!(poly_input[j][poly_input[j].size() - 3] == '^' && poly_input[j][poly_input[j].size() - 2] == '-' && isDigit(poly_input[j][poly_input[j].size() - 1])) && 
                !(poly_input[j][poly_input[j].size() - 2] == '^' && isDigit(poly_input[j][poly_input[j].size() - 1])))
            {
                cout << "\n- INVALID INPUT " << endl;
                cout << "- Term should end with power it is raised too\n" << endl;
                return false;
            }

            // If the first digit of number starts with a zero it should be the last char in term
            if (poly_input[j][loop_start_number] == '0' && loop_start_number + 1 != poly_input[j].size())
            {
                cout << "\n- INVALID INPUT " << endl;
                cout << "- cannot start number with a zero and follow it with another digit or character\n" << endl;
                return false;
            }

            // Checks to see if exponent carrot is the first character
            if (poly_input[j][loop_start_number] == '^')
            {
              cout << "\n- INVALID INPUT " << endl;
              cout << "- Exponent carrot cannot start a term\n" << endl;
              return false;
            }

            // get location of '^' after validation of correct posiiton
            carrot_location = LocateChar(poly_input[j], '^');
            
            if(poly_input[j][carrot_location + 1] == '-')
            {
                current_exponent_value = stringToIntMain(poly_input[j].substr(carrot_location + 2)) * -1;
            }
            else
            {
                current_exponent_value = stringToIntMain(poly_input[j].substr(carrot_location + 1));
            }

            
        }

        //equal temp to the first exponent value and check if polynomial powers in decending order
        if(j == 0)
        {
            temp_exponent_value = current_exponent_value;
        } 
        else
        {
            if(temp_exponent_value <= current_exponent_value)
            {
                cout << "Powers of polynomial must be written in descending order";
                return false;
            }
        }

    } // end of for-loop
    return true;
 }

 int LocateChar(string str, char c)
 {
    for (int i = 0; i < str.length(); i++)
    {
        if(str[i] == c)
        {
            return i;
        }
    }
    return -1;
 }








