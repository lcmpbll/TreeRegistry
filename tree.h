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

    void Add(const Student& newStudent);
    bool Remove(const char* key, Student& aStudent);

    //bool Retrieve(const char* program, Student** sList, int& matches) const;
    bool Edit(const char * key, int standing);
    //int Remove();

    void DisplayAll() const;
    void Monitor() const;
    int GetSize() const {
      return size;
    }
    
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
        left = right = NULL;
	if(aNode.left) {
	  left = new Node(*aNode.left);
	}
	if(aNode.right) {
	  right = new Node(* aNode.right);
	} 

      }
      ~Node() {
        if(data) {
	  delete data;
	}
	left = righ = NULL;
      }
      bool Node::IsFull(){
        if(left && right) return true;
	return false;
      }
      Student * data;
      Node * left;
      Node * right
    };
    Node * root = NULL;
    int size;

    // Call functions on all students
    void ForAll(Node* root, void (*func)(Student& s)) const;
    void ForAll(Node* root, bool (*func)(Student& s));
    // Ordered displays
    void DisplayPre(ostream& out, Node* curr) const;
    void DisplayPost(ostream& out, Node* curr) const;
    void DisplayInOrder(ostream& out, Node* curr) const;
    // Add student recursively
    void Add(Node*& currRoot, const Student& aStudent);
    // Edit tree
    void Copy(Node* src, Node *& dest);
    // Removing nodes
    bool Remove(Node*& currRoot, const char* key, Student& aStudent);
    void Destroy(Node*& root);
    void DeleteNode(Node*& target);
    // Monitor effeciency
    int BranchLength(Node* root) const;
    int LongestBranch(Node* root) const;
};



#endif
    
