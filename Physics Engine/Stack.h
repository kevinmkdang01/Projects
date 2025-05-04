//kxd220039 Kevin Dang
#ifndef STACK_H
#define STACK_H
#include "Data.h"
#include "Node.h"
#include <iostream>

class Stack {
   
private:
   Node* head = nullptr;
   
public:
   //Constructors
   Stack();
   
   //Overloaded constructors
   Stack(Node*);
   
   //Copy constructor
   Stack(Stack&);
   
   //Destructors
    void deleteNodes(Node* current) {
        if (current) {
// Recursively delete nodes
            deleteNodes(current->getNext());
            delete current;
        }
    }
   
   //Mutators
   void setHead(Node* h){head = h;}
   
   //Accessors
   Node* getHead(){return head;}
   
   friend void operator<<(Stack&, Node*&); //Push
   friend void operator>>(Stack&, Node*&); //Pop
   friend std::ostream& operator<<(std::ostream&, Stack&); //Print
   
};

#endif