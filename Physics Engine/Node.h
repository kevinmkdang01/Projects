//kxd220039 Kevin Dang
#ifndef NODE_H
#define NODE_H
#include "Data.h"

class Node {
   
private:
   Data payload;
   Node *next = nullptr;
   
public:
   //Constructors
   Node();
   
   //Overloaded constructors
   Node(Data, Node*);
   Node(Data);
   Node(Node*);
   
   //Destructors
   ~Node(){}
   
   //Mutators
   void setPayload(Data d){payload = d;}
   void setNext(Node* n){next = n;}
   
   //Accessors
   Data getPayload(){return payload;}
   Node* getNext(){return next;}
   
};

#endif