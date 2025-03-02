//File name: Student.h
//Author: Liam Campbell
//Purpose: Declares student class
//Class: CS260
//Asssignment: project 4

#include "constants.h"
#include <iostream>
using namespace std;
#ifndef STUDENT_H
#define STUDENT_H

class Student {
  public:
    Student();
    Student(char* name, char* program, char* gNum, int standing);
    Student(const Student& anStudent);
    ~Student();
    // Friend output function
    const Student& operator= (const Student& anStudent);
    friend ostream& operator<<(ostream& os, const Student& anStudent);
    const Student& operator > (const Student& aStudent);
    // Getters
    void GetName(char* name) const;
    void GetProgram(char* program) const;
    void GetGNumber(char* gNum) const;
    int GetStanding() const;
    // Setters
    void SetName(char* name);
    void SetProgram(char* pro);
    void SetGNumber(char* gNum);
    bool SetStanding(int newStd);
    // Helper for incrementing by one.
    bool IncrementStanding();
    // Prints column headers
    void PrintHeaders() const;
    void Print() const;
    bool IsInProgram(const char* program) const;
    bool IsAtStanding(int stand) const;
    bool IsPoorPerformer() const;
    void Write(ofstream& os) const;
  private: 
    char* program; // Pointer program
    char* gNum; // Pointer to student G Number
    char* name;  // Pointer to lastName
    int standing;      // Integer indicating academic standing
};

#endif

