// File name: student.cpp
// Author: Liam Campbell
// Purpose: function definitions for student class.
// Class: CS 260
// Assignment: project 4

#include "student.h"
#include <cstring>
#include <iomanip>
#include <fstream>

//Name: Default Constructor
//Desc: An student constructed with no parameters will have these values.
//input: none
//output: none
//return: Student
Student::Student(){
  name = new char[strlen("unknown") + 1];
  strcpy(name, "unknown");
  program = new char[strlen("undelcared") + 1];
  strcpy(program, "undeclared");
  gNum = new char[strlen("G0000000") + 1];
  standing = 0;
}

//Name: Constructor
//Desc: An student constructed with set parameters.
//input: none
//output: none
//return: Student
Student::Student(char* name, char* program, char* gNum, int standing) {
  SetName(name);
  SetProgram(program);
  SetGNumber(gNum);
  this->standing = standing;
}

//Name: Copy Constructor
//Desc: Creates a deep copy of an Student
//input: none
//output: none
//return: Student
Student::Student(const Student& anStudent) {

   if (!anStudent.name || !anStudent.gNum || !anStudent.program) {
        name = gNum = program = nullptr;
        return;
    }

  name = new char[strlen(anStudent.name) + 1];
  strcpy(name, anStudent.name);
  program = new char [strlen(anStudent.program) + 1];
  strcpy(program, anStudent.program);
  gNum = new char[strlen(anStudent.gNum) + 1];
  strcpy(gNum, anStudent.gNum);
  standing = anStudent.standing;
}



//Name: Destructor
//Desc: Deallocates memory for pointers in Student
//input: none
//output: none
//return: none
Student::~Student() {
  delete [] name;
  name = NULL;
  delete[] program;
  program = NULL;
  delete[] gNum;
  gNum = NULL;

}

//Name: SetName()
//Desc: Allocates memory and sets name
//input: none
//output: none
//return: none
void Student::SetName(char* name) {
  if(this-> name) {
    delete[] this-> name;
  }
  this-> name = new char[strlen(name) + 1];
  strcpy(this->name, name);
}

//Name: SetProgram()
//Desc: Allocates memory and sets program
//input: none
//output: none
//return: none
void Student::SetProgram(char* program) {
  if(this-> program) {
    delete[] this->program;
  }
  this->program = new char[strlen(program) + 1];
  strcpy(this->program, program);
}

//Name: SetGNumber()
//Desc: Sets student's gNumber
//input: none
//output: none
//return: none
void Student::SetGNumber(char* gNum) {
  if(this->gNum) {
    delete[] this->gNum;
  }
  this->gNum = new char[strlen(gNum) + 1];
  strcpy(this->gNum, gNum);
}

//Name: IncrementStanding() 
//Desc: Increments level by one
//input: none
//output: none
//return: bool
bool Student::IncrementStanding() {
  return SetStanding(standing + 1);
}

//Name: SetStanding()
//Desc: Sets standing for the Student
//input: none
//output: none
//return: none
bool Student::SetStanding(int newStanding) {
  if(newStanding > GRADES -1 || newStanding < 0) {
    return false;
  }
  standing = newStanding;
  return true;
}

//Name: GetName()
//Desc: Returns student's name
//input: none
//output: none
//return: name* by reference.
void Student::GetName(char* rName) const {
  //if(rName) {
   // delete [] rName;
  //}
  //rName = new char[strlen(this->name) + 1];
  strcpy(rName, this->name);
}

//Name: GetProgram()
//Desc: Returns an student's program
//input: none
//output: none
//return: program* by reference.
void Student::GetProgram(char* program) const {  
  if(program) {
    delete [] program;
  }
  program = new char[strlen(this->program) + 1];
  strcpy(program, this->program);
}

//Name: GetGNumber()
//Desc; Returns the gNumber of the student.
//input: none
//output: none
//return: char*& gNumber
void Student::GetGNumber(char* gNum) const {
  if(gNum) {
    delete []gNum;
  }
  gNum = new char[strlen(this->gNum) + 1];
  strcpy(gNum, this->gNum);
}

//Name: GetStanding()
//Desc: Returns the standing of the student
//input: none
//output: none
//return: int standing
int Student::GetStanding() const {
  return standing;
}

//Name: Assignment Operator Overload
//Desc: Overloads the assignment operator to create deep copy of Student
//input: none
//output: none
//return: Student
const Student& Student::operator= (const Student& anStudent) {
  if(this == &anStudent) {
    return *this;
  } else {
    
    char* name = new char[M_CHAR], * gNum = new char [G_CHAR], *program = new char[M_CHAR];
    anStudent.GetName(name);
    anStudent.GetGNumber(gNum);
    anStudent.GetProgram(program);

    this -> SetName(name);
    this -> SetGNumber(gNum);
    this -> SetProgram(program);
    this -> standing = anStudent.standing;
  }
  return *this;
}

//Name: operator overload <<
//Desc: overloads the << operator to print out Student details
//input: none
//output: Student details
//return: none
ostream& operator<<(ostream& os, const Student& anStudent){
  os << left << setw(PROG_W) << anStudent.program;
  os << left << setw(NAME_W) << anStudent.name;
  os << right << setw(GNUM_W) << anStudent.gNum;
  os << right << setw(STAND_W) << STAND[anStudent.standing];
  os << endl;
  return os;
}

//Name: operator overload > 
//Desc: overloads the > operator to compare students
//input: none
//output: none
//return: bool true if gNum > than aStudent.gNum
Student operator>(const Student& aStudent) {
  char tNum[G_CHAR];
  aStudent.GetGNumber(tNum);
  return strcmp(gNum, tNum) > 0;
}

//Name: Print()
//Desc: Uses << operator override to print out student data
//input: none
//output; none
//return; none
void Student::Print() const {
  cout << this;
}

//Name: PrintHeaders()
//Desc: Prints column headers
//input: none
//output: none
//return: void
void Student::PrintHeaders() const {
  cout << "# ";
  cout << left << setw(PROG_W) << "Program";
  cout << left << setw(NAME_W) << "Name";
  cout << right << setw(GNUM_W) << "G Number";
  cout << right << setw(STAND_W) << "Standing" << endl;
}

//Name: IsAtLevel()
//Desc: Returns true if the Student is at the input standing 
//input: none
//output: none
//return: bool true if at the standing
bool Student::IsAtStanding(int stand) const {
  if(standing == stand) {
    return true;
  } else {
    return false;
  }
}

//Name: IsPoorPerformer()
//Desc: Calls IsAtStanding with 0
//input: none
//output: none
//return: bool true if standing is 0, false if not
bool Student::IsPoorPerformer() const {
 return this->IsAtStanding(0);
}

//Name: Write()
//Desc: Output formatted for file
//input: none
//output: Student details formatted for writing to file
//return: none
void Student::Write(ofstream& os) const {
  os << name << ";" << gNum << ";";
  os << program << ";" << standing << ";" << endl;
}
  
//Name: IsInProgram()
//Desc: Returns true is the student is in the passed program
//input: none
//output: none
//return: bool, true if program matches, false if not
bool Student::IsInProgram(const char* program) const {
  return strcmp(program, this->program) == 0;
}


