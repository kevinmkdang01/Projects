  //kxd220039 Kevin Dang
#include <iostream>
#include <cstdio>
#include<fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// Database name used throughout the code in which the final result will be printed   
const string database = "freeplay.dat";

//Structure containing all the elements required for a specific arcade game
struct gameInfo
{
  string name;
  int highScore;
  string initials;
  int plays;
  double revenue;
  gameInfo *next;
};

   //Function used to check and verify things were edited or added properly to the linked list
//Used primarly for debugging, prints all values of a linked list to console and inside sort record
void
printLinkedList (gameInfo * &head) {
  gameInfo *current = head;

// Traverse the linked list
  while (current != nullptr)
	{

// Print the data of the current game
	  
		{
		  cout << current->
			name << ", " << current->highScore << ", " << current->
			initials << ", " << current->plays << ", $" << fixed <<
			setprecision (2) << current->revenue << endl;
		

// Move to the next game
	  current = current->next;
	}
}
}

//This reads through the batch file and reads in the info of the current game and creates a linked list
void addRecordFromFile (string line, gameInfo * &head) {
  string name1, highScore1, initials1, plays1, revenue1;

  // Find the position of the first comma
  size_t comma1 = line.find (',');
  if (comma1 != string::npos)
	{
	  // Extract the name
	  name1 = line.substr (0, comma1);

	  // Find the position of the second comma starting after the first comma
	  size_t comma2 = line.find (',', comma1 + 1);
	  if (comma2 != string::npos)
		{
		  // Extract high score, initials, and plays
		  highScore1 = line.substr (comma1 + 2, comma2 - comma1 - 2);
		  initials1 = line.substr (comma2 + 2, 3);	// Assuming initials are always 3 characters

		  // Find the position of the dollar sign
		  size_t dollarSignPos = line.find ('$', comma2);
		  if (dollarSignPos != string::npos)
			{
			  // Extract plays and revenue
			  size_t playsStart = comma2 + 7;	// Position after the second comma and space
			  size_t playsEnd = dollarSignPos - 1;	// Position before the dollar sign
			  plays1 = line.substr (playsStart, playsEnd - playsStart);
			  revenue1 = line.substr (dollarSignPos + 1);

			  // Convert string values to appropriate types
			  gameInfo *newGame = new gameInfo;
			  newGame->name = name1;
			  newGame->highScore = stoi (highScore1);
			  newGame->initials = initials1;
			  newGame->plays = stoi (plays1);
			  // Convert revenue string to double after removing the dollar sign
			  newGame->revenue = stod (revenue1);

			  // Insert the new game into the linked list
			  if (head == nullptr)
				{
				  head = newGame;
				  newGame -> next = nullptr;
				}
			  else
				{
				  gameInfo *temp = head;
				  while (temp->next != nullptr)
					{
					  temp = temp->next;
					}

					  temp->next = newGame;
                  newGame -> next = nullptr;
				}
			}
		}
	}
}

//Adds a new record from a singular line
void
addRecord (string line, gameInfo * &head)
{

//Separates all the variables of the line in order to prepare for the next step
  string name1, highScore1, initials1, plays1, revenue1;
  size_t nameStart = line.find ('"');
  size_t nameEnd = line.find ('"', nameStart + 1);
  name1 = line.substr (nameStart + 1, nameEnd - nameStart - 1);
  size_t highScorePos = line.find (' ', nameEnd);
  size_t initialsPos = line.find (' ', highScorePos + 1);
  size_t playsPos = line.find (' ', initialsPos + 1);
  size_t revenuePos = line.find (' ', playsPos + 1);
  highScore1 = line.substr (highScorePos + 1, initialsPos - highScorePos - 1);
  initials1 = line.substr (initialsPos + 1, playsPos - initialsPos - 1);
  plays1 = line.substr (playsPos + 1, revenuePos - playsPos - 1);
  revenue1 = line.substr (revenuePos + 2);

//Prints out to user the information parsed
  cout << "RECORD ADDED" << endl;
  cout << "Name: " << name1 << endl;
  cout << "High Score: " << highScore1 << endl;
  cout << "Initials: " << initials1 << endl;
  cout << "Plays: " << plays1 << endl;
  cout << "Revenue: $" << setprecision (2) << fixed << revenue1 << endl <<
	endl;

//Creates a new gameInfo with the information parsed from the line
  gameInfo *newGame = new gameInfo;
  newGame->name = name1;
  newGame->highScore = stoi (highScore1);
  newGame->initials = initials1;
  newGame->plays = stoi (plays1);
  newGame->revenue = stod (revenue1);

//Adds to the beginning of the linked list
  if (head == nullptr)
	{
	  head = newGame;
	  newGame -> next = nullptr;
	}
//If not at the beginning, add to the end
  else
	{
	  gameInfo *temp = head;
	  while (temp->next != nullptr)
		{
		  temp = temp->next;
		}
	  temp->next = newGame;
	  newGame -> next = nullptr;
	}
}

//Looks through the linked list for a specific name
void
searchRecord (string searchTerm, gameInfo * head)
{
  bool found = false;
  gameInfo *current = head;

//Conditional statement to check if it's at the end of the linked list or not
  while (current != nullptr)
	{
// Converts the names to lowercase to avoid case sensitivity
		  string lowerName = current->name;
//Compares the strings, if found, prints to console it is found
	  if (lowerName.find (searchTerm) != string::npos)
		{
			found = true;
		  cout << current->name << " FOUND" << endl;
		  cout << "High Score: " << current->highScore << endl;
		  cout << "Initials: " << current->initials << endl;
		  cout << "Plays: " << current->plays << endl;
		  cout << "Revenue: $" << setprecision (2) << fixed <<
			current->revenue << endl << endl;
	}
// Moves onto next, does not end loop in case for multiple with the same term
  current = current->next;
}

//If none at all are found, output to console, none found
if (!found)
  {
	cout << searchTerm << " NOT FOUND" << endl;
  }
}

//Edits a gameInfo based on the field number
void
editRecord (string line, gameInfo * head)
{
  gameInfo *current = head;

// Parses the line to identify the field number and separate the information
  string name1, fieldNumber, newValue;
  size_t nameStart = line.find ('"');
  size_t nameEnd = line.find ('"', nameStart + 1);
  name1 = line.substr (nameStart + 1, nameEnd - nameStart - 1);
  size_t fieldNumberPos = line.find (' ', nameEnd);
  size_t newValuePos = line.find (' ', fieldNumberPos + 1);
  fieldNumber =
	line.substr (fieldNumberPos + 1, newValuePos - fieldNumberPos - 1);
  newValue = line.substr (newValuePos + 1);

//Uses same logic as the previous search function in order to find the desired
//gameInfo to edit
  while (current != nullptr)
	{

		  string lowerName = current->name;
		  string lowerName1 = name1;

	  if (lowerName == lowerName1)
		{


//If field number is 1, update the high score by assigning it a new value
			  if (fieldNumber == "1")
				{

				  current->highScore = stoi (newValue);

				  cout << current->name << " UPDATED" << endl;
				  cout << "UPDATE TO high score " << "- VALUE " << newValue <<
					endl;
//If field number is 2, update the initials to a new value
				}
			  else if (fieldNumber == "2")
				{
				  cout << current->name << " UPDATED" << endl;
				  cout << "UPDATE TO initials " << "- VALUE " << newValue <<
					endl;
				  current->initials = newValue;

//If field number is 3, update the plays to a new value and in doing so updates the revenue as well
				}
			  else if (fieldNumber == "3")
				{
				  int newPlays = stoi (newValue);
				  current->plays = newPlays;
				  current->revenue = newPlays * 0.25;
				  cout << current->name << " UPDATED" << endl;
				  cout << "UPDATE TO plays " << "- VALUE " << newValue <<
					endl;

				}


//If a gameInfo is successfully edited, print to console 
			  cout << "Name:" << current->name << endl;
			  cout << "High Score: " << current->highScore << endl;
			  cout << "Initials: " << current->initials << endl;
			  cout << "Plays: " << current->plays << endl;
			  cout << "Revenue: $" << setprecision (2) << fixed <<
				current->revenue << endl << endl;
			  
//End function
			  break;
			  
			
		}

//Moves to the next value in linked list if not found successfully
	  current = current->next;

	}


}

void
deleteRecord (string line, gameInfo *&head)
{
    if (head != nullptr){
  bool found = false;
  gameInfo *current = head;
  gameInfo *prev = nullptr;

  // Conditional statement to check if it's at the end of the linked list or not
  while (current != nullptr)
	{
	  // Converts the names to lowercase to avoid case sensitivity

		  string lowerName = current->name;

	  // Compares the strings, if found, deletes the game
	  if (lowerName.find (line) != string::npos)
		{

		  found = true;
		  cout << "RECORD DELETED" << endl;
		  cout << "Name: " << current->name << endl;
		  cout << "High Score: " << current->highScore << endl;
		  cout << "Initials: " << current->initials << endl;
		  cout << "Plays: " << current->plays << endl;
		  cout << "Revenue: $" << setprecision (2) << fixed <<
			current->revenue << endl << endl;
			  

		  if (prev == nullptr)
			{
			  head = current->next;
			  delete current;
			  break;

			}
		  else if (current->next != nullptr)
			{
			  prev->next = current->next;
			  delete current;
			  break;
			}
		  else if (current->next == nullptr)
			{
			  prev->next = nullptr;
			  delete current;
			  break;
			}


		}

	  prev = current;
	  current = current->next;
	}

// If none at all are found, output to console, "not found"
  if (!found)
	{
	  cout << "NOT FOUND" << endl;
	}
    }
}





void sortRecord (string line, gameInfo *&head) {
  // List is empty or has only one game, no need to sort
  if (head == nullptr || head->next == nullptr)
	{
	  return;
	}
  // Variables to keep track of the previous and current nodes during traversal
  gameInfo *prev = nullptr;
  gameInfo *index = nullptr;
  gameInfo *current = head;

  bool swapped = true;
  // Traverse the list until no more swaps are needed
  while (swapped){
      swapped = false;
      current = head;
      prev = nullptr;
      if ( current -> next != nullptr){
      index = current->next;
      }
      else index = nullptr;
    while(current->next !=nullptr && current != nullptr){
        index = current->next;
            if (line == "name"){
            if(current->name > current->next->name){
                //head swap
                if (prev == nullptr){
                    head = index;
                    current->next = index->next;
                    index->next = current;
                    prev=index;
                }
                //tail swap
                else if(index->next == nullptr){
                    prev->next=index;
                    current->next = nullptr;
                    index->next=current;
                    swapped = true;
                }
                //middle
                else {                        
                        prev->next = index;
                        current->next = index->next;
                        index->next = current;
                        prev = index;
                        swapped = true;
                }
            }
            else{
                prev = current;
                current= current->next;
            }
        }
        else if (line == "plays"){
            if(current->plays > current->next->plays){
                //head swap
                if (prev == nullptr){
                    head = index;
                    current->next = index->next;
                    index->next = current;
                    prev=index;
                }
                //tail swap
                else if(index->next == nullptr){
                    prev->next=index;
                    current->next = nullptr;
                    index->next=current;
                    swapped = true;
                }
                //middle
                else {                        
                        prev->next = index;
                        current->next = index->next;
                        index->next = current;
                        prev = index;
                        swapped = true;
                }
            }
            else{
                prev = current;
                current= current->next;
            }
        }
        else break;
    }    
  }

  if (line == "plays") {
	  cout << "RECORDS SORTED BY plays" << endl;
	}
  else if (line == "name")
	{
	  cout << "RECORDS SORTED BY name" << endl;
	}
  // Print the sorted list
  printLinkedList (head);
}

void
printNodeToFile (gameInfo * current, fstream & outputFile)
{
  // If list is empty

  if (current == nullptr)
	{
	  return;
	}

  // Print current game's data to the file

  outputFile << current->
	name << ", " << current->highScore << ", " << current->
	initials << ", " << current->plays << ", $" << fixed << setprecision (2)
	<< current->revenue << endl;
			  

  // Recursively print the rest of the list
  printNodeToFile (current->next, outputFile);

}

void deleteLinkedList(gameInfo  *&head) {
    gameInfo* current = head;
    while (current != nullptr) {
        gameInfo* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr; // Set head to null to indicate that the list is empty
}






int main ()
{
  //Copied from project 1
  /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
  string temp;					//variable for database filename
  string batch;					//variable for batch filename

  cout << "Enter Database Name: ";
  cin >> temp;
  cin >> batch;
  gameInfo *head = nullptr;
  fstream databaseFile (database, ios::out);
  fstream logFile (temp, ios::out | ios::in);
  fstream batchFile (batch, ios::in | ios::out);

  string id, name, score, initials, plays, revenue;
  string currentLine, tempIn, Line;
  vector < string > logLines, batchLines;

  //Puts all the lines from the log file into a vector
  while (getline (logFile, Line))
	{
	  logLines.push_back (Line);
	}
  //Adds all the lines individually from the log file into the linked list
for (string & Line:logLines)
	{
	  addRecordFromFile (Line, head);
	}
  //Puts all the lines from the batch file into a vector
  while (getline (batchFile, Line))
	{
	  batchLines.push_back (Line);
	}
  //Interprets the number, determining the action, and then inputting the rest of the 
  //line into the desired action's function
for (string & Line:batchLines)
	{
	  string inputLine = Line.substr (2);
	  if (Line.at (0) == '1')
		{
		  addRecord (inputLine, head);
		}
	  else if (Line.at (0) == '2')
		{
		  searchRecord (inputLine, head);
		}
	  else if (Line.at (0) == '3')
		{
		  editRecord (inputLine, head);
		}
	  else if (Line.at (0) == '4')
		{
		  deleteRecord (inputLine, head);
		}
	  else if (Line.at (0) == '5')
		{
		  sortRecord (inputLine, head);
		}
	}
  //Used to check linked list during debugging
  //printLinkedList(head);

  //Prints all the linked list contents to the output file
  printNodeToFile (head, databaseFile);
  deleteLinkedList(head);

  //Closes all files used in main
  databaseFile.close ();
  logFile.close ();
  batchFile.close ();
}
