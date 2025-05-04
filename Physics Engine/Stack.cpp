//kxd220039 Kevin Dang
#include "Data.h"
#include "Stack.h"
#include "Node.h"
#include <iostream>

Stack::Stack(){
   head = nullptr;
}
Stack::Stack(Node* h){
   head = h;
}

//copy constructor
Stack::Stack(Stack &other) {
    head = nullptr;

    if (other.head) {
        head = new Node(other.head->getPayload());
        Node* current = head;
        Node* otherCurrent = other.head->getNext();

        while (otherCurrent) {
            current->setNext(new Node(otherCurrent->getPayload()));
            current = current->getNext();
            otherCurrent = otherCurrent->getNext();
        }
    }
}

//Removes the top node
void operator>>(Stack& stack, Node*& poppedNode) {
    if (stack.head) {
        poppedNode = stack.head;
        stack.head = stack.head->getNext();
        poppedNode->setNext(nullptr);
    } else {
        poppedNode = nullptr;
    }
}

//Adds to the top node
void operator<<(Stack& stack, Node*& newNode) {
    if (newNode) {
        newNode->setNext(stack.head);
        stack.head = newNode;
    }
}

//Prints to console contents of the stack
std::ostream& operator<<(std::ostream& os, Stack& stack) {
//Makes sure if stack is empty
    if (!stack.head) {
        os << "Stack is empty";
        return os;
    }

    bool containsOperators = (stack.head->getPayload().getOperator() != ' ');

    Node* current = stack.head;
    while (current) {
        if (containsOperators) {
            os << current->getPayload().getOperator();
        } else {
            os << current->getPayload().getOperand();
        }
        if (current->getNext()) {
            os << ", ";
        }
        current = current->getNext();
    }
    return os;
}