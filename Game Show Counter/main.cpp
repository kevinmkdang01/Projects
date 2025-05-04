//Kevin Dang kxd220039

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int fileLines (string& fileName){
   ifstream file(fileName);
   
   int lineCount = 0;
   
   string line;
   while(getline(file, line)){
      lineCount++;
   }
   file.close();
   return lineCount;
}

string removeSpace(string& input){
   string result; 
   for (char ch: input){
      if (ch != ' '){
         result.push_back(ch);
      }
   }
   return result;
}

// bool answerChecker(char* ){
// }

// bool validAnswer(){
// }

// void arraySort(){
   
// }

// void createContProfiles(){
   
// }

// void contSummary(){
// }


int main (){
   string answerFile, contestantResponse, answerLine, contID, contestantAns;
   int answerLength;
   cin >> answerFile;
   cin >> contestantResponse;
   
   ifstream answers(answerFile);
   ifstream contestant(contestantResponse);
   
   answerLength = fileLines(answerFile);
   
   //answer key
   char* answer = new char[answerLength];
   //contestant answer choices
   char* contAns = new char[answerLength];
   //whether they got it right or wrong
   bool* rightWrong = new bool [answerLength];
   
   
   
   char ans;
   int i = 0;
   while(answers >> ans){
      
      answer[i] = ans;
      i++;
   }
   
   while(contestant){
      getline(contestant, contID);
      if(contID.size() >= 12){
      contestantAns = contID.substr(11);
      contID = contID.substr(0,10);
      contestantAns = removeSpace(contestantAns);
      }
      
   for (int i = 0; i < answerLength; i++) {
      contAns[i] = contestantAns[i];
   }
   
      for(int i = 0 ; i < answerLength; i++){
         if(contAns[i]==answer[i]){
            rightWrong[i] = true;
         }
         else rightWrong[i] = false;
      }
      
      string allWrong = "";
      string answerKeyRight = "";
      string contAnsWrong = "";
      int amountWrong = 0;
      
      for(int i = 0; i < answerLength; i++){
         if(!rightWrong[i]){
            
            allWrong+= to_string(i+1);
            if (i < answerLength-1){
               allWrong += ' ';
            }
            answerKeyRight += answer[i];
            if(i < answerLength-1){
               answerKeyRight += ' ';
            }
            contAnsWrong += contAns[i];
            if(i < answerLength-1){
               contAnsWrong += ' ';
            }
         }
         else amountWrong++;
      }
      
      double aW = static_cast<double>(amountWrong);
      double grade = (aW/answerLength)*100;
      cout << contID << " - " << fixed << setprecision(2) << grade << endl;
      cout << allWrong << endl;
      cout << contAnsWrong << endl;
      cout << answerKeyRight << endl << endl;
      
      
      
   }
   
   delete [] answer;
   delete[] contAns;
   delete[] rightWrong;
   
   answers.close();
   contestant.close();
   return 0;
}