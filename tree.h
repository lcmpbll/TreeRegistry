//File Name: table.h
//Author: Liam Campbell
//Date; 2/28/2025
//Desc: Declares table ADT
//Class: CS260
//Assignment: project 4

#ifndef TREE_H
#define TREE_H

#include "constants.h"
#include "student.h"
using namespace std;

class Tree {
  public:
    Tree();
    Tree(const char* fileName);
    Tree(const Tree& aTree);
    ~Tree();
    void Destroy();

    void Add(const Student& newStudent);
    bool Retrieve(const char* program, Student** sList, int& matches) const;
    bool Edit(const char * key, int standing);
    int Remove();
    void DisplayAll() const;
    void Monitor() const;
    int GetSize() const {
      return size;
    }
    void GrowTree();
    
    void LoadFromFile(const char* fileName);
    bool SaveToFile(const char* fileName) const;
    const Tree& operator= (const Tree& aTree);
  private:
    struct Node {
      Node(const Student& aStudent) {
        data = new Student(aStudent);
	left = right = NULL;
      }
      
      Node(const Node& aNode) {
        data = new Student(*(aNode.data));
	if(aNode.next) {
	  left = new Node(*aNode.left);
	  right = new Node(* aNode.right);
	} else {
	  left = right = NULL;
	}
      }
      ~Node() {
        if(data) {
	  delete data;
	}
	left = righ = NULL;
      }
      Student * data;
      Node * left;
      Node * right
    };
    int currentCap;
    Node * root = NULL;
    const static int INIT_CAP = 11;
    int size;

    int CalculateIndex(const char* key, int cap = 0) const;
    void Destroy(Node* head);
    bool IsPrime(int num);
    int NextCap(int nextCap);
};

#endif
    
