//kxd220039 Kevin Dang
#ifndef DATA_H
#define DATA_H

class Data {
private:
   double operand;
   char op = ' ';
   
public:
   // Constructors
   Data();
   
   //Overloaded constructors
   Data(double);
   Data(char);
   Data(double,char);

   // Mutators
   void setOperand(double o) { operand = o; }
   void setOperator(char o) { op = o; }

   // Accessors
   double getOperand() const { return operand; }
   char getOperator() const { return op; }
};

#endif