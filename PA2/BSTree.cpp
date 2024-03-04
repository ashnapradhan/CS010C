#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void BSTree::insert(const string& key) {
  // Edge case:  The tree is empty
  // Edge case: If we find the key in the tree, just increment its count
  // Typical case, we find a hole where this key belongs
  // ==> if we would go left and there is no child there, insert new node to left
  // ==> if we would go right and there is no child there, insert new node to right

  
  Node* newKey = new Node(key); // create new node of the inserting key
  Node* currNode = root; // to start traverse

  if (root == nullptr) { //if empty
    root = newKey; //if empty, then make root the new node
  }
  else if (search(key)) { //else if the key is already there
    while (currNode != nullptr) { //while not at end of BST
    if (currNode->key == key) { //if key is found
      currNode->count++; //increment count
      return;
    }
    else if (currNode->key > key) { //else, if key is smaller than curr key
      currNode = currNode->left; //go to left for smaller keys
    }
    else { //else, if key is greater
      currNode = currNode->right; //go to right for greater keys
    }
  }
  }
  else { //if key is not in BST
     while (currNode != nullptr) { //while not at end
      if (newKey->key < currNode->key) { //if new key is less than curr key
      if (currNode->left == nullptr) { //if no left child
        currNode->left = newKey; //insert at left
        currNode = nullptr;
        }
      else {
        currNode = currNode->left; //else, move to next left node
        }
      }
    else { //else, if new key is greater than curr key
      if (currNode->right == nullptr) { //and no right child
        currNode->right = newKey; //insert at right 
        currNode = nullptr;
      }
      else {
        currNode = currNode->right; //else, move to next right node
        }
      }
    }
  }
}
bool BSTree::search(const string& key) const {
  // Search can be done in a loop (or recursively).  A loop is best here
  if (root == nullptr) { //check if empty
    return false; //return false if empty
  }

  Node* node = root; //to start traverse
  while (node != nullptr) { //while not at end
    if (key < node->key) { //if search key is less than curr key
      node = node->left; //move to left nodes
    }
    else if (key > node->key) { //else if key is greater than curr key
      node = node->right; //move to right nodes
    } 
    else { //else if key == curr key
      return true; //return true
    }
  }
  return false;

}

string BSTree::largest() const {

  if (root == nullptr) { //if BST is empty
    return ""; //return empty string
  }

  Node* currNode = root; //to start traverse

  while (currNode->right != nullptr) { //while not at end
    currNode = currNode->right; //continue going right to find largest key
  }

  return currNode->key; //return largest key
 
  // Edge case: Tree is empty (return "")
  // Largest can be done in a loop (or recursively).  A loop is best here
}

string BSTree::smallest() const {

  if (root == nullptr) { //if BST is empty
    return ""; //return empty string
  }

  Node* currNode = root; //to start traverse

  while (currNode->left != nullptr) { //while not at end
    currNode = currNode->left; //continue going left to find largest key
  }


  return currNode->key; //return largest key

  // Smallest can be done in a loop (or recursively).  A loop is best here
  // Edge case: Tree is empty
}

int BSTree::height(const string& key) const {

 if (root == nullptr) { //check if empty
  return -1; // return -1 if empty
 }

 if (!search(key)) { //if key not found
    return -1; //return -1
  }

 if (root->key == key) { //if key is at root
  return height_of(root); //get height from root
 }

 Node* currNode = root; //else, start traverse

 while (currNode != nullptr && currNode->key != key) { //while not at end and key not found
  if (key < currNode->key) { //if key is less than curr key
    currNode = currNode->left; //move left
  }
  else { //if key is greater than curr key
    currNode = currNode->right; //move right
  }
 }

 return height_of(currNode); //use height function

  // First find the node with this key, then run "height_of" to get
  // the height that zybooks wants
}

void BSTree::remove(const string& key) {
  remove(root, root, key); //use helper function
}

void BSTree::preOrder() const {
  preOrder(root); //use helper function
  cout << endl; //new line
}

void BSTree::postOrder() const {
  postOrder(root); //use helper function
  cout << endl; //new line
  // This wants a ", " after each node and exactly one newline once done
}

void BSTree::inOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  inOrder(root); //use helper function
  cout << endl; //new line
}

void BSTree::remove(Node* parent, Node* tree, const string& key) {

  if (!search(key)) { //if key not found
    return; //do nothing
  }
  Node* succNode = nullptr; //initialize successor

  while(tree->key != key) { //while key not found
    if (tree->key > key) { //if curr key is greater
      parent = tree; //parent is one node higher
      tree = tree->left; //move to left
    }
    else { //if curr key is smaller
      parent = tree; //parent is one node higher
      tree = tree->right; //move to right
    }
  }

  if (tree->count > 1) {//if current count > 1
    tree->count--; //decrement to remove
  }
  else if (tree->count == 1) { //if current count == 1
    if (tree->left == nullptr && tree->right == nullptr) { //if curr node is leaf
      if (parent->left == nullptr && parent->right == nullptr) { //if at root
        delete tree; //delete curr node
        root = nullptr;
        return;
      }
      else if (tree == parent->left) { //if curr node is left child 
        delete tree; //delete curr node
        parent->left = nullptr; //set left child as null
        return;
      }
      else if (tree == parent->right) { //if curr node is right child
        delete tree; //delete curr node
        parent->right = nullptr; //set right child as null
        return;
      }
    }
    else { //if node is not leaf
      if (tree->left != nullptr) { //if left child exists
        succNode = tree->left; //successor is on left side
        while (succNode->right != nullptr) { //while no right child
          succNode = succNode->right; //successor is right most child
        }
        tree->key = succNode->key; //curr key is now successor's key
        tree->count = succNode->count; //curr count is now successor's count
        succNode->count = 1; //successor count = 1
        remove(tree, tree->left, tree->key); //recursive call
        return;
      }
      else  { //else, if right child exists
        succNode = tree->right; //successor is on right side
        while (succNode->left != nullptr) { //while no left child
          succNode = succNode->left; //successor is left most child
        }
        tree->key = succNode->key; //curr key is now successor's key
        tree->count = succNode->count; //curr count is now successor's count
        succNode->count = 1; //successor count = 1
        remove(tree, tree->right, tree->key); //recursive call
        return;
      }
    }
  }


}

int BSTree::height_of(Node* tree) const {
  // The height (length of longest path to the bottom) of an empty tree is -1
  // Otherwise, you pick the larger of the left height and the right height
  // and add one to that
  
  if (tree == nullptr) { //if empty tree
    return -1;
  }

  int leftHeight = height_of(tree->left); //recursive call for LHS
  int rightHeight = height_of(tree->right); //recursive call for RHS

  return 1 + max(leftHeight, rightHeight); //return max height

}

void BSTree::preOrder(Node* tree) const {
 
  if (tree == nullptr) { //check if empty
    return;
  }
  cout << tree->key << "(" << tree->count << "), "; //print
  preOrder(tree->left); //recursive call for LHS
  preOrder(tree->right); //recursive call for RHS
  

}

void BSTree::postOrder(Node* tree) const {

  if (tree == nullptr) { //check if empty 
    return;
  }
  postOrder(tree->left); //recursive call for LHS
  postOrder(tree->right); //recursive call for RHS
  cout << tree->key << "(" << tree->count << "), "; //print

}

void BSTree::inOrder(Node* tree) const {
 
  if (tree == nullptr) { //check if empty
    return;
  }
  inOrder(tree->left); //recursive call for LHS
  cout << tree->key << "(" << tree->count << "), "; //print
  inOrder(tree->right); //recursive call for RHS

}




/*
// This is a pre-order traversal that shows the full state of the tree
// (but it is a code turd)
void BSTree::debug(Node* tree, int indent) const {
  if (tree == nullptr) return;
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << tree << ' ' << *tree << endl;
  debug(tree->left,indent+1);
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << "-" << endl;
  debug(tree->right,indent+1);
}
*/
