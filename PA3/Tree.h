#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( ) : root(nullptr) {}
  ~Tree( );
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  // Add additional functions/variables here
  void destructor(Node*);
  void insertHelp(Node*, const string&);
  void splitInsert(Node*, const string&);
  void preOrder(Node*) const;
  void inOrder(Node*) const;
  void postOrder(Node*) const;
  void remove(Node*, const string&);
  bool search (Node*, const string &) const;
  Node* searchNode(Node*, const string &); 
    
};

#endif