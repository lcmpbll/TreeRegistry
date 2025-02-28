//File name: main.cpp
//Author: Liam Campbell
//Desc: Defines the function responsible for interacting with the user.
//Class: CS260
//Asssignment: project 4
/*Program Desc: This program acts as a registry for students holding data about heir programs of study and performance. 
*/
#include "main.h"
#include "student.h"
#include "tree.h"
#include <cstring>
#include <iostream>
using namespace std;

//Name: main()
//Desc: Manages user input and calls the program functions.
//input: char menuOption
//output: Menu and feedback for file operations.
//return: 0
int main() {
  Student currentStudent;
  Student** sList = NULL;
  Tree registry(FILENAME);
  char option;//, userInput[M_CHAR];
  int nStand, num;
  char prog[M_CHAR];
  char name[M_CHAR];
 
  Welcome();
  do {
    Menu();
    GetOption(option);
    switch (option) {
      case 'e':
	registry.DisplayAll();
        cout << "Enter the name of the student you would like to edit: ";
	GetChars(name);
	StandingChart(); 
	cout << "Enter " << name << "'s new standing: " << endl;
	GetInt(nStand, 0);
	if(registry.Edit(name, nStand)) {
	  cout << name << "'s Grade updated to " << STAND[nStand] << endl;
        } else { 
          cout << "Could not update standing" << endl;
        }	  
	break;
      case 'r':
        num = registry.Remove();
	cout << num << " students removed" << endl;
	break;
      case 'g':
	cout << "Which program would you like to see: ";
	GetChars(prog);
	sList = new Student*[registry.GetSize()];
	for(int i = 0; i < registry.GetSize(); i ++) {
	  sList[i] = NULL;
	}
	if(registry.Retrieve(prog, sList, num)) {
	  cout << num << " students in " << prog << endl;
          Display(sList, num);
       } else {
         cout << "No students in " << prog << endl;
       }	 
       num = 0;
       delete [] sList;
       sList = NULL;
       break;
      case 'd':
	registry.DisplayAll();
	break;
      case 'm':
	cout << "List Effeciency: "<< endl;
	registry.Monitor();
        break;
      case 'a':
	GetNewStudent(currentStudent);
	registry.Add(currentStudent);
	break;
      case 'q':
      default: 
	if(registry.SaveToFile(FILENAME)) {
	  cout << "Saved to " << FILENAME << endl;
	} else {
	  cout << "Ending program queue not saved." << endl;
	}
	break;
    }
  } while (option != 'q'); 
  return 0;
}

//Name: Welcome()
//Desc: Welcomes the user
//input: none
//output: none
//return: none
void Welcome () {
  cout << "Welcome to the Command doer undoer program." << endl;
}

//Name: Menu()
//Desc: Displays the main menu
//input: none
//output: none
//return: none
void Menu () {
  cout << "Make a selection from the list below: " << endl;
  cout << "(D)ISPLAY REGISTRY" << endl;
  cout << "(E)DIT STUDENT" << endl;
  cout << "(A)DD A STUDENT" << endl;
  cout << "(R)EMOVE UNDER PERORMERS" << endl;
  cout << "(G)ET PROGRAM" << endl;
  cout << "(M)ONITOR EFFECIENCY" << endl;
  cout << "(Q)UIT" << endl;
}

//Name: GetOption()
//Desc: Reads the user's option selection, verifies it is an option.
//input: char option
//output: Error if selection is invalid
//return: option, by reference
void GetOption(char& option) {
  cout << "Enter your selection: " << endl;
  cin >> option;
  cin.ignore(100, '\n');
  option = tolower(option);
  while (!cin || !InOptions(option)) {
    cin.clear();
    option = '\0';
    Menu();
    GetOption(option);
  }
}

//Name: InOptions()
//Desc: Tests to see wether the value is in the options list.
//input: none
//output: none
//return: bool true if present, false if not
bool InOptions(char& option, int index) {
  if(index == TOTAL_OPTIONS) {
    return false;
  } else if(option == OPTIONS[index]) {
    return true;
  } else {
    return InOptions(option, index + 1);
  }
}

//Name: GetInt()
//Desc: Gets an integer from a user with in min and max
//input: int 
//output: instructions to user
//return: int selectedInt
void GetInt(int& input, const int min) {
  cin >> input;
  cin.ignore(100, '\n');
  if(!cin || (input < min)) {
    cout << "Please enter a non negative integer." << endl;
    input = -2;
    cin.clear();
    GetInt(input, min);
  }
}

//Name: GetChars()
//Desc: Gets user input
//input: char* input[]
//output: none
//return: none
void GetChars(char* input) {
  cin.getline(input, M_CHAR);
}

//Name: Display()
//Desc: Displays the student list
//input: none
//output: student list
//return: none
void Display(Student ** sList, int num) {
  sList[0]->PrintHeaders();
  for(int i = 0; i < num; i ++) {
    if(sList[i]) {
      cout << *(sList[i]);
    }
  }
}

//Name: StandingChart()
//Desc: Displays the possible stanind entries and their meanings
//input: none
//output: standing chart
//return: none
void StandingChart() {
  for(int i = 0; i < GRADES; i++) {
    cout << i << ": " << STAND[i] << endl;
  }
}

//Name: GetNewStudent()
//Desc: Gathers information for a new student
//input: student details
//output: prompts for student details
//return: student by reference
void GetNewStudent(Student& student) {
  char temp[M_CHAR];
  int stand;

  cout << "Enter the student's full name: ";
  GetChars(temp);
  student.SetName(temp);
  memset(temp, '\0', M_CHAR);

  cout << "Enter the student's program of study: ";
  GetChars(temp);
  student.SetProgram(temp);
  memset(temp, '\0', M_CHAR);

  cout << "Enter the student's GNumber: ";
  GetChars(temp);
  student.SetGNumber(temp);
  memset(temp, '\0', M_CHAR);

  StandingChart();
  cout << "Enter the student's current standing: ";
  GetInt(stand, 0);
  student.SetStanding(stand);

}
