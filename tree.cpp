//File Name: table.cpp
//Author: Liam Campbell
//Date 2/17/2025
//Desc: Define Table ADT functions
//Class: CS260
//Assignment: project 3


#include "table.h"
#include "student.h"
#include <fstream>
#include <cstring>
using namespace std;

//Name: Default Constructor
//Desc: Creates a Table with default parameters
//input: none
//output: none
//return: Table
Table::Table() {
  currentCap = INIT_CAP;
  Node ** aTable = new Node*[currentCap];
  for(int i = 0; i < currentCap; i ++) {
    aTable[i] = NULL;
  }

  size = 0;
}

//Name: Constructor
//Desc: Creates a Table loaded from file
//input: infile
//output: none
//return: Table
Table::Table(const char* fileName) {
  currentCap = INIT_CAP;
  aTable = new Node*[currentCap];
  for(int i = 0; i < currentCap; i ++) {
    aTable[i] = NULL;
  }

  size = 0;

  LoadFromFile(fileName);
}

//Name: Copy Constructor
//Desc: Creates a table that is a copy of the table
//input: none
//output: none
//return: Table
Table::Table(const Table& bTable ) {
  if(this->aTable) {
    delete [] this->aTable;
  }
  this->currentCap = bTable.currentCap;
  this->aTable = new Node* [currentCap];

  int index = 0;
  //Iterate through aTable
  while(index < bTable.currentCap) {
    Node* curr = bTable.aTable[index];
    while(curr) {
      Add(*(curr->data));
      curr=curr->next;
    }
    index ++;
  }
  
}

// Name: Destructor
// Desc: Frees memory that was allocated for the table
// input: none
// output: none
// return: none
Table::~Table() {
  if(!aTable) return;
  for(int i = 0; i < currentCap; i ++) {
    if(aTable[i]) {
      Destroy(aTable[i]);
      aTable[i] = NULL;
    }
  }
  delete [] aTable;
  aTable = NULL;
}

//Name: Destroy()
//Desc: Iterates through used portions of table freeing memory recursively
//input: none
//output: none
//return: none
void Table::Destroy(Node* head) {
  if(head) {
    if(head->next) {
      Destroy(head->next);
    }
    delete head;
  }
}

//Name: Add()
//Desc: Places a new student in the table
//input: none
//output: none
//return: none
void Table::Add(const Student& newStudent) {
  Node* newNode = new Node(newStudent);
  int index;
  bool placed = false;
  char* key = new char[M_CHAR];
  
  newStudent.GetName(key);
  index = CalculateIndex(key);

  if(aTable[index] == NULL) {
    aTable[index] = newNode;
  } else {
    Node * curr = aTable[index];
    while(curr && !placed) {
      if(curr->next == NULL) {
        curr->next = newNode;
        placed = true;
      } else {
	curr = curr->next;
      }
    }
  }
  delete [] key;  
  size ++;
  if(size > (currentCap/3) * 4) {
    GrowTable();
  }
}

//Name: GrowTable()
//Desc: Increases currentCap and opies table with new cap.
//input: none
//output: none
//return: aTable
void Table::GrowTable() {
  int newCap = NextCap(currentCap * 2 + 1); // increases capacity, by at least 2 to next prime number
  Node** newTable = new Node*[newCap]; // allocates memory for new table
  int index = 0; // keeps track of index
  Node* curr = NULL, *next = NULL;  // holds current node
  char * key = new char[M_CHAR]; // Temp char* for student name

  for(int i =0; i < newCap; i ++) {
    newTable[i] = NULL;
  }

  while(index < currentCap) {
    curr = aTable[index];
    while(curr) {
      next = curr->next;
      curr->data->GetName(key);	    
      int newIndex = CalculateIndex(key, newCap);

      curr->next = newTable[newIndex];
      newTable[newIndex] = curr;
      curr = next;
    }
    index ++;
  }
  delete[] aTable;
  delete [] key;
  aTable = newTable;
  currentCap = newCap;
}

//Name: LoadFromFile() 
//Desc: Loads student data from a file.
//input: none
//output: none
//return: none
void Table::LoadFromFile(const char* fileName) {
  Student aStudent; // acts as temp student to pass to table
  char name[M_CHAR], program[M_CHAR], gNum[M_CHAR];
  int standing = 0;  // student property
  ifstream infile; //input file 
  
  infile.open(fileName);
  if(infile) {
    while(!infile.eof()) {
      infile.getline(name, M_CHAR, ';');
      aStudent.SetName(name);
      infile.getline(gNum, G_CHAR, ';');
      aStudent.SetGNumber(gNum);
      infile.getline(program, M_CHAR, ';');
      aStudent.SetProgram(program);
      infile >> standing;
      infile.ignore(1, ';');
      infile.ignore(1, '\n');
      aStudent.SetStanding(standing);
      if(!infile.fail()) {
	 Add(aStudent);
      } else {
	infile.close();
      }
    }
    if(infile) {
      infile.close();
    } 
  }
}

//Name: SaveToFile()
//Desc: Saves data to file
//input: none
//output: student data to file
//return: bool, true if successful, false if not.
bool Table::SaveToFile(const char* fileName) const {
  ofstream outfile;
  int index = 0;
  Node* curr = NULL;
  
  outfile.open(fileName);
  if(outfile.is_open()) {
    while(index < currentCap) {
      curr = aTable[index];
      while(curr) {
        curr->data->Write(outfile);
	curr = curr->next;
      }
      index ++;
    }
    outfile.close();
    return true;
  }

  return false;
}
	  
//Name: Retrieve()
//Desc: Travels through list counts and returns students in the specified program
//input: none
//output: none
//return: bool true if students found, false if not
bool Table::Retrieve(const char* program, Student** sList, int& matches) const {
  Node* curr = NULL;
  int index = 0;
  matches = 0;

  while(index < currentCap) {
    curr = aTable[index];
    while(curr) {
      if(curr->data && curr->data->IsInProgram(program)) {
        sList[matches] = curr->data;
        matches ++;
      }
      curr = curr->next;
    }
    index ++;
  }
  if(matches > 0) {
    return true;
  } else {
    return false;
  }
}

//Name: Edit()
//Desc: Edits the standing of the student that matches the key
//input: none
//output: none
//return: bool true if matching student found and stading incremented
bool Table::Edit(const char* key, int standing) {
  Node* curr = NULL;
  int index = CalculateIndex(key);
  char* name = new char[M_CHAR];

  curr = aTable[index];
  do {
    if(curr) {
      curr->data->GetName(name);
      if(strcmp(name, key) == 0) {
        curr->data->SetStanding(standing);
	delete [] name;
	name = NULL;
	return true;
      } else {
	curr = curr->next;
      }
   }
  } while (curr);
  delete[] name; 
  name = NULL;
  return false;
} 

//Name: Remove()
//Desc: Removes students from the list if they are in poor standing.
//input: none
//output: none
//return: int the number of students removed
int Table::Remove() {
  int removed = 0, index = 0;
  Node* curr = NULL, * prev;

  while(index < currentCap) {
    curr = aTable[index];
    prev = NULL;
    while(curr) {
      if(curr->data->IsPoorPerformer()) {
	Node* remove = curr;
	curr = curr->next;
        if(prev) {	 
          prev->next = curr;
	} else {
	  aTable[index] = curr;
	}
          delete remove;
	  removed ++;
	  size --;
      } else {
	prev = curr;
	curr = curr->next;
      }
    }
    index ++;
  }
  return removed;
}


//Name: Monitor() 
//Desc: Displays the number of table spots that are full and the length of the chain if there is more than one.
//input: none
//output: table stats
//return: none
void Table::Monitor() const {
  int index = 0, count = 0;
  Node* curr = NULL;

  while(index < currentCap) {
    curr = aTable[index];
    count = 0;
    while(curr) {
       count ++;  
       curr = curr->next;
    } 
      cout << index << ": " << count << endl;
      index ++; 
  }
}

//Name: DisplayAll()
//Desc: Prints out all the students 
//input: none
//output: All Students
//return: none
void Table::DisplayAll() const {
  int index = 0, count = 1;
  Node* curr = NULL;
  
  cout << "Display Table: " << endl;
  while(index < currentCap) {
   curr = aTable[index];
   while(curr) {
      if(count == 1) {
	 curr->data->PrintHeaders();
      }
     
      cout << count << ". ";
      cout << *(curr->data);
      count ++;

      curr = curr->next;
    }
    index ++;
  }
  cout << endl;
  
}
    
//Name: CalculateIndex()
//Desc: Calculates the index for the table based on the key
//input: none
//output: none
//return: int index;
int Table::CalculateIndex(const char* key, int cap) const {
  if(cap == 0) cap = currentCap;
  int index = 0;
  int hashResult = 0;
  for(; *key != '\0'; key++) {
    hashResult += *key + index;
    index ++;
  }
  return hashResult % cap;
}

//Name: IsPrime()
//Desc: Returns true if the number is prime
//input: none
//output: none
//return: bool, true if prime false if not
bool Table::IsPrime(const int num) {
  if(num < 2) return false;
  if(num == 2 || num == 3) return true;
  if(num % 2 == 0 || num % 3 == 0) return false;

  for(int i = 5; i * i <= num; i += 6) {
    if(num % i == 0 || num % (i + 2) == 0) return false;
  }
  return true;
}

//Name: NextCap()
//Desc: Finds the next prime number to be the Cap
//input: none
//output: none
//return: int nextCap
int Table::NextCap(int nextCap) {
  if(!IsPrime(nextCap)) {
   NextCap(nextCap += 2);
  }
  return nextCap;
}
