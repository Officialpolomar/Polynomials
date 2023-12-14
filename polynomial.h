#include <string>
#include <iostream>
using namespace std;

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {

private:
struct Node{

int coefficient;
int exponent;
Node* next;

};
Node* head = nullptr;
int length = 0;

int stringToInt(string);
bool isdigit(char);
bool isVariable(string);

public:
//~Polynomial();
   

void stringToList(string*, int, int);
void displayTerms() const ;
void appendNode(int, int);
void operator=(const Polynomial& polyCopy);
void deleteList();
int getCoefficient(int) const ;
int getExponent(int) const ;
int getLength() const;
bool isEmpty() const;



// void parsePolyInput(string,int, string*);

};








#endif