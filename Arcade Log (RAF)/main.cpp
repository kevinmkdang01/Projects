// Kevin Dang kxd220039
// This code uses random access files in order to edit and store a database of arcade machine information
// Using a batch file to read commands from, it creates and edits the database of information
// It includes multiple functions in order to add, search, edit, and delete the information
// This code has validity functions that check that the inputs and batch file to make sure it can go through
// the functions properly without error
// The code also checks that the files were opened properly
// If the last two subjects were not done correctly, the code will abort and exit

#include <iostream>
#include <cstdio>
#include<fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

const string database = "database.dat";  
//your filestream for the database will connect to this variable

// This function is used to make all characters in a string lowercase in order to
// compare and ignore case sensitivity.
string toLower(string input){
   string result;
   int size = static_cast<int>(input.size());
   for (int i = 0; i < size; i++){
      result+= static_cast<char>(tolower(input.at(i)));
   }
   return result;
}

// This function adds a line to the database and output to console
// the information it had inputted
void addRecord (string line, string fileName = database){
   ofstream outFile(fileName, ios::app);
   if(!(outFile.is_open())){
      return;
   }
   string name, highScore, initials, plays, revenue;
   size_t nameStart = line.find('"');
   size_t nameEnd = line.find('"', nameStart+1);
   name = line.substr(nameStart + 1, nameEnd- nameStart - 1);
   size_t highScorePos = line.find(' ', nameEnd);
   size_t initialsPos = line.find(' ', highScorePos +1);
   size_t playsPos = line.find(' ', initialsPos + 1);
   size_t revenuePos = line.find(' ', playsPos + 1);
   highScore = line.substr(highScorePos + 1, initialsPos-highScorePos-1);
   initials = line.substr(initialsPos + 1, playsPos - initialsPos - 1);
   plays = line.substr(playsPos + 1, revenuePos-playsPos-1);
   revenue = line.substr(revenuePos+2);
   
   cout << "RECORD ADDED" << endl;
   cout << "Name: " << name << endl;
   cout << "High Score: " << highScore << endl;
   cout << "Initials: " << initials << endl;
   cout << "Plays: " << plays << endl;
   cout << "Revenue: $" << setprecision(2) << fixed << revenue << endl << endl;
   outFile << name << ", " << setfill('0') << setw(9) << highScore << ", " << initials << ", " << setfill('0') << setw(4) << plays << ", $" << setfill('0') << setw(7) << setprecision(2) << revenue << endl;
   outFile.close();
}

//This function copies over everything to a temp file except for the 
// desired database to delete then makes the temp file the new file
void deleteRecord (string line, string fileName = database){
   ifstream ogFile(fileName, ios::in);
   ofstream tempFile("temp.txt");
      if(!(tempFile.is_open())){
      return;
   }
      if(!(ogFile.is_open())){
      return;
   }
   
      
      string name = line;
      string highScore, initials, plays, revenue, finalOutput; 
      string lowerSearch = toLower(name);
      string fileLine, foundLine;
      bool found = false;
    
      while(getline(ogFile, fileLine)){
         string lowerFileLine = toLower(fileLine);
         if(lowerFileLine.find(lowerSearch) != string::npos){
            foundLine = fileLine;
            size_t nameEnd = foundLine.find(',');
            name = foundLine.substr(0, nameEnd);
            string lowerName = toLower(name);
            
            
            
            size_t highScorePos = foundLine.find(' ', nameEnd);
            size_t initialsPos = foundLine.find(' ', highScorePos +1);
            size_t playsPos = foundLine.find(' ', initialsPos + 1);
            size_t revenuePos = foundLine.find(' ', playsPos + 1);
            highScore = foundLine.substr(highScorePos + 1, initialsPos-highScorePos-2);
            initials = foundLine.substr(initialsPos + 1, playsPos - initialsPos - 2);
            plays = foundLine.substr(playsPos + 1, revenuePos-playsPos-2);
            revenue = foundLine.substr(revenuePos+2);
            
            if(lowerName==lowerSearch){
               found = true;
            }
            else if (lowerName != lowerSearch){
               tempFile << fileLine << endl;
            }
            
         }
         else {
            tempFile << fileLine << endl;
            }
      }
         ogFile.close();
         tempFile.close();
         
            if (found == true){
               remove(fileName.c_str());
               rename("temp.txt",fileName.c_str());
               
               cout << "RECORD DELETED" << endl;
               cout << "Name: " << name << endl;
               cout << "High Score: " << stoi(highScore) << endl;
               cout << "Initials: " << initials << endl;
               cout << "Plays: " << stoi(plays) << endl;
               cout << "Revenue: $" << setprecision(2) << fixed << stod(revenue) << endl << endl;
               
            }
            else if (found == false){
            }
            else{};

}

//This function takes in a line and depending on the field number
//edits a part of the database line 
void editRecord (string line, string fileName = database){
   fstream totalFile(fileName, ios::in | ios::out);
         if(!(totalFile.is_open())){
      return;
   }
   string name, fieldNumber, newValue;
   double newRev;
   size_t nameStart = line.find('"');
   size_t nameEnd = line.find('"', nameStart+1);
   name = line.substr(nameStart + 1, nameEnd - nameStart - 1);
   size_t fieldNumberPos = line.find(' ', nameEnd);
   size_t newValuePos = line.find(' ', fieldNumberPos + 1);
   fieldNumber = line.substr(fieldNumberPos + 1, newValuePos - fieldNumberPos -1);
   newValue = line.substr(newValuePos+1);
      string highScore, initials, plays, revenue, finalOutput; 
      string lowerSearch = toLower(name);
      string fileLine, foundLine;
      bool found = false;
    
      while(getline(totalFile, fileLine)){
         string lowerFileLine = toLower(fileLine);
         if(lowerFileLine.find(lowerSearch) != string::npos){
            foundLine = fileLine;
            nameEnd = foundLine.find(',');
            name = foundLine.substr(0, nameEnd);
            size_t highScorePos = foundLine.find(' ', nameEnd);
            size_t initialsPos = foundLine.find(' ', highScorePos +1);
            size_t playsPos = foundLine.find(' ', initialsPos + 1);
            size_t revenuePos = foundLine.find(' ', playsPos + 1);
            highScore = foundLine.substr(highScorePos + 1, initialsPos-highScorePos-2);
            initials = foundLine.substr(initialsPos + 1, playsPos - initialsPos - 2);
            plays = foundLine.substr(playsPos + 1, revenuePos-playsPos-2);
            revenue = foundLine.substr(revenuePos+2);
            found = true;
             if (fieldNumber == "1"){
             totalFile.seekp(-31, ios::cur);
             highScore = newValue;
             totalFile << setfill('0') << setw(9) << highScore;
             }
                else if (fieldNumber == "2"){
                  totalFile.seekp(-20, ios::cur);
                  initials = newValue;
                  totalFile  << initials;
                }
                   else if (fieldNumber == "3"){
                     totalFile.seekp(-15, ios::cur);
                     plays = newValue;
                     newRev = stoi(plays)*0.25;
                     totalFile << setfill('0') << setw(4) << plays << ", $" << setfill('0') << setw(6) << setprecision(2) << newRev;
                   }
                

         }
         else {};
      }

         totalFile.clear();

            if (found == true){

             if (fieldNumber == "1"){
             cout << name << " UPDATED" << endl;
             cout << "UPDATE TO high score " << "- VALUE " << newValue << endl;
             cout << "Name: " << name << endl;
             cout << "High Score: " << stoi(highScore) << endl;
             cout << "Initials: " << initials << endl;
             cout << "Plays: " << stoi(plays) << endl;
             cout << "Revenue: $" << setprecision(2) << fixed << stod(revenue) << endl << endl;
   }
   else if (fieldNumber == "2"){

            cout << name << " UPDATED" << endl;
            cout << "UPDATE TO initials " << "- VALUE " << newValue << endl;
            cout << "Name: " << name << endl;
            cout << "High Score: " << stoi(highScore) << endl;
            cout << "Initials: " << initials << endl;
            cout << "Plays: " << stoi(plays) << endl;
            cout << "Revenue: $" << setprecision(2) << fixed << stod(revenue) << endl << endl;
   }
   else if (fieldNumber == "3"){
             cout << name << " UPDATED" << endl;
             cout << "UPDATE TO plays " << "- VALUE " << newValue << endl;
             cout << "Name: " << name << endl;
             cout << "High Score: " << stoi(highScore) << endl;
             cout << "Initials: " << initials << endl;
             cout << "Plays: " << stoi(plays) << endl;
             cout << "Revenue: $" << setprecision(2) << fixed << newRev << endl << endl;
   }
   else {};
            }
            else if (found == false){
            }
            else{};
totalFile.close();

}

// Checks the record if there is the desired string located
// even checks for those with the string as a part of the total title
void searchRecord (string line, string fileName = database){
      string name, highScore, initials, plays, revenue, finalOutput; 
      ifstream outFile(fileName, ios::in);
            if(!(outFile.is_open())){
      return;
   }
      string lowerSearch = toLower(line);
      string fileLine, foundLine;
      bool found = false;
      while(getline(outFile, fileLine)){
         string lowerFileLine = toLower(fileLine);
         if(lowerFileLine.find(lowerSearch) != string::npos){
            foundLine = fileLine;
            
            
            size_t nameEnd = foundLine.find(',');
            name = foundLine.substr(0, nameEnd);
            size_t highScorePos = foundLine.find(' ', nameEnd);
            size_t initialsPos = foundLine.find(' ', highScorePos +1);
            size_t playsPos = foundLine.find(' ', initialsPos + 1);
            size_t revenuePos = foundLine.find(' ', playsPos + 1);
            highScore = foundLine.substr(highScorePos + 1, initialsPos-highScorePos-2);
            initials = foundLine.substr(initialsPos + 1, playsPos - initialsPos - 2);
            plays = foundLine.substr(playsPos + 1, revenuePos-playsPos-2);
            revenue = foundLine.substr(revenuePos+2);
            found = true;
             cout << name << " FOUND" << endl;
             cout << "High Score: " << stoi(highScore) << endl;
             cout << "Initials: " << initials << endl;
             cout << "Plays: " << stoi(plays) << endl;
             cout << "Revenue: $" << setprecision(2) << fixed << stod(revenue) << endl << endl;
   
         }
         else {};
      }
            if (found == false){
               cout << line << " NOT FOUND" << endl;
            }
   outFile.close();
}

// Validates all input for the adding record function
bool validAte1 (string input){
   string name, highScore, initials, plays, revenue, finalOutput;
   size_t nameStart = input.find('"');
   size_t nameEnd = input.find('"', nameStart+1);
   string nameInspect = input.substr(nameStart, nameEnd- nameStart +1);
   name = input.substr(nameStart+1, nameEnd-nameStart-1);

      if(nameInspect.front() != '"' || nameInspect.back() != '"'){
      return false;
   }
   
   string afterName = input.substr(nameEnd-nameStart-1);
   
      int stored = 0 ;
      
   for (int i = 0; i < static_cast<int>(afterName.length()); i++){
      if ( afterName.at(i) == ' '){
         stored++;
      }
   }
   if (stored != 4){
      return false;
   }
   
    for (int i = 0; i < static_cast<int>(afterName.length()); i++){
      if ( afterName.at(i) == '\t'){
         return false;
      }
   }
   
   
   size_t highScorePos = input.find(' ', nameEnd);
   size_t initialsPos = input.find(' ', highScorePos +1);
   size_t playsPos = input.find(' ', initialsPos + 1);
   size_t revenuePos = input.find(' ', playsPos + 1);
   highScore = input.substr(highScorePos + 1, initialsPos-highScorePos-1);
   initials = input.substr(initialsPos + 1, playsPos - initialsPos - 1);
   plays = input.substr(playsPos + 1, revenuePos-playsPos-1);
   revenue = input.substr(revenuePos+1);
   
   for (char c: highScore){
      if(!isdigit(c)){
         return false;
      }
   }
   
   if(highScore.length() > 10){
      return false;
   }
   
   if (initials.find(' ') != string::npos || initials.length() > 4){
      return false;
   }
   
   for (char c: plays){
      if (!isdigit(c)){
         return false;
      }
   }
   
   if (plays.length()>5){
      return false;}
      
   size_t dollarPos = revenue.find('$');
   if (dollarPos == string::npos){
      return false;
   }
   
   if (revenue.find('.', dollarPos)==string::npos){
      return false;
   }
   string beforeDec = revenue.substr(dollarPos+1, revenue.find('.')-dollarPos-1);
   string afterDec = revenue.substr(revenue.find('.')+1);
   if ((beforeDec.length()>4)|| (afterDec.length()!=2)){
      return false;
      }
      
   return true;
}

//There needs to be no validation aside from a string for the search
// function as it searches for the entirety of the string 
bool validAte2 (string input){
   string in = input;
   return true;
}

//Validates the inputs for the input string to make sure it does not error out
bool validAte3 (string input){
   
   string name, fieldNumber, newValue;
   
   size_t nameStart = input.find('"');
   size_t nameEnd = input.find('"', nameStart+1);
   name = input.substr(nameStart + 1, nameEnd - nameStart - 1);
   size_t fieldNumberPos = input.find(' ', nameEnd);
   size_t newValuePos = input.find(' ', fieldNumberPos + 1);
   fieldNumber = input.substr(fieldNumberPos + 1, newValuePos - fieldNumberPos -1);
   newValue = input.substr(newValuePos+1);
   
   
   
      
   
   string nameInspect = input.substr(nameStart, nameEnd- nameStart +1);
   name = input.substr(nameStart+1, nameEnd-nameStart-1);

      if(nameInspect.front() != '"' || nameInspect.back() != '"'){
      return false;
   }
     if (static_cast<int>(fieldNumber.length())!= 1){
      return false;
   }
   

   if ( (stoll(fieldNumber) < 1) || (stoll(fieldNumber) > 3)){
      return false;
   }
   
   string afterName = input.substr(nameEnd-nameStart-1);
   
      int stored = 0 ;
      
   for (int i = 0; i < static_cast<int>(afterName.length()); i++){
      if ( afterName.at(i) == ' '){
         stored++;
      }
   }
   if (stored != 2){
      return false;
   }
   
      
     if (fieldNumber == "1"){
        
      if(static_cast<int>(newValue.length())>10LL){
         return false;
      }
      
      for(char c: newValue){
         if(!isdigit(c)){
            
            return false;
         }
      }
      
      int newHighScore = static_cast<int>(stoll(newValue));
      if((newHighScore < 0) || (newHighScore > 999999999)){
         return false;
      }
      
   }
   
   else if (fieldNumber == "2"){
      if (newValue.find(' ') != string::npos || newValue.length() > 4){
       
         return false;
         
      }
      
   }
   
   else if (fieldNumber == "3"){
      if (newValue.length()>5){
         
         return false;
      }
      for (char c: newValue){
         if (!isdigit(c)){
            
            return false;
         }
      }
   }
   else return false;
   
   
    for (int i = 0; i < static_cast<int>(afterName.length()); i++){
      if ( afterName.at(i) == '\t'){
         return false;
      }
   }
   

   
 
   
   
   return true;
}

// Deletes any record with the following string, so it does not validation
bool validAte4 (string input){
   string in = input;
   return true;
}

//Validates the entirety of the batch file line to make sure it is readable
//and fits the argument of the database function and validation functions
bool validAte (string input){
   if (input.at(1) ==' '){
   if (input.at(0) == '1' || input.at(0) == '2'|| input.at(0) == '3' || input.at(0) == '4'){
      string newString = input.substr(2);
      switch(input.at(0)){
         case '1':
         return validAte1(newString);
         break;
         case '2':
         return validAte2(newString);
         break;
         case '3':
         return validAte3(newString);
         break;
         case '4':
         return validAte4(newString);
         break;
         default:
         return false;
      }
   }
   
   }
   return false;
}

int main(){
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
   string temp;  //variable for database filename
   string batch; //variable for batch filename

   cout<<"Enter Database Name: ";
   cin>>temp;

   ifstream infile(temp, ios::binary);
   ofstream outfile(database, ios::binary);
   string line;
   if (infile)
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
                outfile << line << "\n";
        }

   infile.close();
   outfile.close();
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
   cin >> batch;
   
   fstream databaseFile(database, ios::out | ios::in);
   fstream logFile(temp, ios :: out | ios:: in);
   fstream batchFile(batch, ios:: in | ios::out);
   
   string id, name, score, initials, plays, revenue;
   string currentLine, tempIn, Line;
   vector<string> logLines, batchLines; 
// Goes through the entirety of the current database and stores that
//within a vector
   while (getline(logFile, Line)){
   logLines.push_back(Line);
   }
   for (string& Line: logLines){
      databaseFile << Line << endl;
   }
   
//Goes through the entirety of the batch file and stores each line as a string
//allowing for the database and validity functions to be able to utilize them
   while (getline(batchFile, Line)){
   batchLines.push_back(Line);
   }
   for (string& Line: batchLines){
      string inputLine = Line.substr(2);
      
   if(validAte(Line)){
      if (Line.at(0)=='1'){
         addRecord(inputLine);
      }
      else if (Line.at(0) =='2'){
         searchRecord(inputLine);
      }
      else if (Line.at(0) == '3'){
         editRecord(inputLine);         
      }
      else if (Line.at(0) == '4'){
         deleteRecord(inputLine);  
      }
   }
   }
   

   
   
   
   databaseFile.close();
   logFile.close();
   batchFile.close();
}
