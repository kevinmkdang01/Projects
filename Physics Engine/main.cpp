//kxd220039 Kevin Dang
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include "Stack.h"
#include "Data.h"
#include "Node.h"

using namespace std;

//Print all the values in a stack, used for debugging
void printStackOperands(Stack& stack) {
    Node* current = stack.getHead();
//Loops through entire stack and prints out, then moves the current to the next pointer
    while (current != nullptr) {
        cout << current->getPayload().getOperand() << " ";
        current = current->getNext();
    }
    cout << endl;
}

//Returns the value for each operator, could have used enum but didn't
//For values in infix to postfix to compare the precendence
int getPriority(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
   else if (op == '^')
      return 3;
    else
        return 0;
}

//Inline of Node and Data types
Node::Node(){
   payload = Data();
   next = nullptr;
}
Node::Node(Data d, Node* n){
   payload = d;
   next = n;
}
Node::Node(Data d){
   payload = d;
}
Node::Node(Node* n){
   next = n;
}
Data::Data(){
   op = ' ';
   operand = 0.0;
}
Data::Data(double d){
   operand = d;
}
Data::Data(char c){
   op = c;
}
Data::Data(double d, char c){
   op = c;
   operand = d;
}

//Checks if the value is a digit or a period, if not it will return false
bool isNumeric(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch) && ch != '.') {
            return false;
        }
    }
    return true;
}


//Function to take a single string line to convert it to postfix string
string infixToPostfix(const string& expression) {
//Declaring values
    Stack operators;
    string postfix;
    string operand; 
    
//Loops through all the character values of the string
    for (char ch : expression) {
//Checks for numeric value or period, if it is add to postfix string
        if (isdigit(ch) || ch == '.') {
            operand += ch; 
        } else if (isspace(ch)) {
//Checks if its at the end of the operand, if not already add a space and then clears preparing for the next operand
            if (!operand.empty()) {
                postfix += operand; 
                postfix += ' ';
                operand.clear(); 
            }}
//Checks for opening parenthesis 
            else if (ch == '(') {
            if (!operand.empty()) {
                postfix += operand;
                postfix += ' '; 
                operand.clear(); 
            }
//Creates a Data object with parenthesis as its character and then adds it to the stack
            Data d(ch);
            Node* newNode = new Node(d);
            operators << newNode;
        } 
//Checks for closing parenthesis
        else if (ch == ')') {
            if (!operand.empty()) {
                postfix += operand;
                postfix += ' '; 
                operand.clear();
            }
            
//Pops operators from stack and add them to postfix
            while (operators.getHead() && operators.getHead()->getPayload().getOperator() != '(') {
                Node* poppedNode;
                operators >> poppedNode;
                postfix += poppedNode->getPayload().getOperator();
                postfix += ' '; 
                delete poppedNode;
            }
//Removes open parenthesis from stack
            if (operators.getHead() && operators.getHead()->getPayload().getOperator() == '(') {
                Node* poppedNode;
                operators >> poppedNode;
                delete poppedNode;
            }
        } else {
            if (!operand.empty()) {
                postfix += operand;
                postfix += ' ';
                operand.clear();
            }
            while (operators.getHead() && getPriority(operators.getHead()->getPayload().getOperator()) >= getPriority(ch)) {
                Node* poppedNode;
                operators >> poppedNode;
                postfix += poppedNode->getPayload().getOperator();
                postfix += ' ';
                delete poppedNode;
            }
            Data d(ch);
            Node* newNode = new Node(d);
            operators << newNode;
        }
    }
//Add the rest of the operands to postfix
    if (!operand.empty()) {
        postfix += operand;
        postfix += ' ';
    }
//Pop and add the remaining operators
    while (operators.getHead()) {
        Node* poppedNode;
        operators >> poppedNode;
        postfix += poppedNode->getPayload().getOperator();
        postfix += ' ';
        delete poppedNode;
    }
    
    return postfix;
}

//Checks if it is a valid operator character
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

double evaluatePostfix(const string& postfix) {
    Stack operands;

    size_t start = 0;
    size_t end = 0;

//Finds the value before and after the operator using spaces
    while (end < postfix.size()) {

        while (end < postfix.size() && !isspace(postfix[end])) {
            ++end;
        }
        string line = postfix.substr(start, end - start);
        start = ++end;


//Evaluates the postfix
        if (isOperator(line[0])) {
            if (operands.getHead() == nullptr || operands.getHead()->getNext() == nullptr) {
                return 0.0;
            }
//Adds to the stack and holds the values within the nodes in order to evaluate
            Node* operand2Node;
            operands >> operand2Node;
            double operand2 = operand2Node->getPayload().getOperand();
            delete operand2Node;

            Node* operand1Node;
            operands >> operand1Node;
            double operand1 = operand1Node->getPayload().getOperand();
            delete operand1Node;

//Checks which operation to do based on operator
            double result;
            switch (line[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        cerr << "Error: Division by zero!" << endl;
                        return 0.0;
                    }
                    result = operand1 / operand2;
                    break;
                case '^':
                    result = pow(operand1, operand2);
                    break;
                default:
                    cerr << "Error: Invalid operator" << endl;
                    return 0.0;
            }
            Data d(result);
            Node* newNode = new Node(d);
            operands << newNode;
        } else {
// If the line is not an operator, it's assumed to be a numeric operand.
// Convert the line to a double using stod.
             {
                double operand = stod(line);
                Data d(operand);
                Node* newNode = new Node(d);
                operands << newNode;
            } 
        }
    }
//Return final results
    if (operands.getHead()) {
        double finalResult = operands.getHead()->getPayload().getOperand();
        return finalResult;
    } else {
        cerr << "Error: Empty expression" << endl;
        return 0.0;
    }
}
   
   
   


int main(){
//Prompts user for filename
   string filename;
   cout << "Enter filename: ";
   cin >> filename;
   ifstream file(filename);
       if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return 1;
    }
//Retrieves string from file to run through function to return specific formatted output
    string expression;
    while(getline(file, expression)){
       string post = infixToPostfix(expression);
       cout << post << '\t' << setprecision(3) << fixed << evaluatePostfix(post) << endl;
    }
    
   
   file.close();
return 0;
}