//File Name: tree.cpp
//Author: Liam Campbell
//Date 2/28/ 2025
//Desc: Define Tree ADT functions
//Class: CS260
//Assignment: project 4


#include "tree.h"
#include "student.h"
#include <fstream>
#include <cstring>
using namespace std;

//Name: Default Constructor
//Desc: Creates a Tree with default parameters
//input: none
//output: none
//return: Tree
Tree::Tree() {
  root = NULL;
  size = 0;
}

//Name: Constructor
//Desc: Creates a Tree loaded from file
//input: infile
//output: none
//return: Tree
Tree::Tree(const char* fileName) {
  Tree();
  LoadFromFile(fileName);
}

//Name: Copy Constructor
//Desc: Creates a table that is a copy of the table
//input: none
//output: none
//return: Tree
Tree::Tree(const Tree& bTree ) {
  if(root) {
    Destroy(root);
  } 
  *this = bTree;
}

// Name: Destructor
// Desc: Frees memory that was allocated for the table
// input: none
// output: none
// return: none
Tree::~Tree() {
  Destroy(root);
}

//Name: Destroy()
//Desc: Iterates through used portions of table freeing memory recursively
//input: none
//output: none
//return: none
void Tree::Destroy(Node*& currRoot) {
  if(currRoot) {
    Destroy(currRoot->left);
    Destroy(currRoot->right);
    delete currRoot->data;
    delete currRoot;
    currRoot = NULL;
  }
  // Base case do nothing}
}

//Name: Add()
//Desc: Passes new student to recursive add increments size.
//input: none
//output: none
//return: none
void Tree::Add(const Student& newStudent) {
  Add(this->root, newStudent);
  size ++;
}

//Name: Add()
//Desc: Recursively Adds a student to the tree.
//input: none
//output: none
//return: none
void Tree::Add(Node*& currRoot, const Student& newStudent) {
  if(!currRoot) {
    currRoot = new Node(newStudent);
  } else if(*(currRoot->data) > newStudent) {
    Add(currRoot->left, newStudent);
  } else {
    Add(currRoot->right, newStudent);
  }
  
} 

//Name: = operator override
//Desc: Overrides the = operator to set one table equal to another
//input: none
//output: none
//return: this
const Table& Table::operator(const Table& srcT) {
  if(this == &srcT) {
    return *this;
  } 
  
  if(this->root) {
    Destroy(this->root);
  } 
  
  size = srcT.size;
  copy(srcT.root, this->root);
  return *this;
}

//Name: Copy()
//Desc: Copies a source node and sub tree to destination tree
//input: none
//output: none
//return: none
void Table::Copy(Node* srcN, Node*& destN) {
  if(srcN) {
    destN = new Node(*(srcN->data));
    Copy(srcN->left, destN->left);
    Copy(srcN->right, destN->right);
  } else {
    destN = NULL;
  }
}


//Name: LoadFromFile() 
//Desc: Loads student data from a file.
//input: none
//output: none
//return: none
void Tree::LoadFromFile(const char* fileName) {
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
bool Tree::SaveToFile(const char* fileName) const {
  ofstream outfile;
  
  outfile.open(fileName);
  if(outfile.is_open() && this->root) {
    SaveToFile(outfile, this->root);
    outfile.close();
    return true;
  }

  return false;
}

//Name: SaveToFile()
//Desc: Recursively Writes each object the file.
//input: none
//output: student data to file
//return: none
void Tree::SaveToFile(ostream& out, Node* currRoot) const {
  if(currRoot) {
    //Preorder
    currRoot->data->Write(out);
    SaveToFile(out, currRoot->left);
    SaveToFile(out, currRoot->right);
  }
}
	  
//Name: Retrieve()
//Desc: Travels through list counts and returns students in the specified program
//input: none
//output: none
//return: bool true if students found, false if not
bool Tree::Retrieve(const char* key, Student& student) const {
  char temp[G_CHAR];
  return Retrieve(key, root, student); 
}

bool Tree::Retrieve (const char* key, Node* currRoot, Student& student) const {
  char temp[G_CHAR];
	
  if(currRoot) {
    int comp = strcmp(key, temp);
    if(comp == 0) {
      student = currRoot->data;
      return true;
    } else if(comp < 0) {
      Retrieve(key, currRoot->left, student);
    } else {
      Retrieve(key, currRoot->right, student);
    }
  }
  return false;
}

//Name: RemoveProgram()
//Desc: Removes students from the list if they are in poor standing.
//input: none
//output: none
//return: int the number of students removed
int Tree::RemoveProgram(const * key) {
  int removed = 0;
  RemoveIf(root, root->data->IsInProgram(key), removed);
  return removed;
}

//Name: RemoveIf() 
//Desc: Removes students recursively from list if they match the parameters
//input: none
//output: none
//return: int number of students removed
void Tree::RemoveIf(Node* currRoot, bool *(func)(const char* key), int& removed) {
  if(currRoot) {
    RemoveIf(currRoot->left, func(key), removed);
    RemoveIf(currRoot->right, func(key), removed);
    if(currRoot.func(key)) {
      DeleteNode(currRoot);
      size --;
      removed ++;  
    } 
  }
}


//Name: Monitor() 
//Desc: Displays the number of table spots that are full and the length of the chain if there is more than one.
//input: none
//output: table stats
//return: none
void Tree::Monitor() const {
  

}

//Name: DisplayAll()
//Desc: Prints out all the students 
//input: none
//output: All Students
//return: none
void Tree::DisplayAll(ostream& out, Node* currRoot) const {
  if(!currRoot) {
    out << "No Students registered." << endl;
    return;
  }
  currRoot->data->PrintHeaders();
  DisplayInOrder(out, currRoot);
}
    
//Name: DisplayInOrder()
//Desc: Displays the student information in order
//input: none
//output: none
//return: none
void Tree::DisplayInOrder(ostream& out, Node* currRoot) {
  if(currRoot) {
    DisplayinOrder(out, currRoot->left);
    out << *(currRoot->data) endl;
    DisplayInOrder(out, currRoot->right);
  }
}


