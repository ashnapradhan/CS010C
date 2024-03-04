#include "Tree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

//constructor
Tree::Tree() : root(nullptr) {}

//destructor
Tree::~Tree() {
    destructor(root);
}

//destructor recursive helper
void Tree::destructor(Node* curr) {
    if(curr == nullptr) { //check if empty
        return;
    }
    //traverse through tree
    destructor(curr->left);
    destructor(curr->middle);
    destructor(curr->right);

    //delete while traversing
    delete curr;
}

void Tree::insert(const string& inserting) {

    if(root == nullptr) { //check if empty
        root = new Node(inserting); //if empty, then insert at root
        return;
    }

    //else, use recursive helper
    insertHelp(root, inserting);

}

void Tree::insertHelp(Node* curr, const string& inserting) {

    if (curr == nullptr) { //check if empty
        return;
    }

    //if new string is greater than curr small string
    if (inserting > curr->small) {
        //if curr is not full
        if (curr->count == 1) {
            //if node is leaf
            if (curr->right == nullptr) {
                //insert new string at node->large
                curr->large = inserting;
                //increment count
                ++curr->count;
            }
            else {
                //if not leaf, traverse through RHS
                insertHelp(curr->right, inserting);
            }
        }
        //if node is full and new string is in between existing strings
        else if (curr->count == 2 && inserting < curr->large) {
            //if middle string exists
            if (curr->middle != nullptr) {
                //call for recursive helper functions
                insertHelp(curr->middle, inserting);
            }
            //if middle key does not exist
            else {
                //call split helper
                splitInsert(curr, inserting);
            }

        }

        else {
            splitInsert(curr, inserting);
        }

    }

    //if new string is smaller than both keys of curr node
    if (inserting < curr->small) {
        //if curr node is not full
        if (curr->count == 1) {
            //if target is leaf
            if (curr->left == nullptr) {
                //shift the current small string to large key
                curr->large = curr->small;
                //place new key in curr->small
                curr->small = inserting;
                //increment count
                ++curr->count;
            }
            else {
                //recursive call for helper function
                insertHelp(curr->left, inserting);
            }
        }
        //if curr node is full
        else if (curr->count == 2) { 
            //if left child exists
            if (curr->left != nullptr) {
                //recursive call 
                insertHelp(curr->left, inserting);
            }
            //if node is leaf
            else {
                //call for split helper function
                splitInsert(curr, inserting);
            }
        }
        else {
            splitInsert(curr, inserting);
        }
    }

    return;

}


void Tree::splitInsert(Node* curr, const string& newStr) {

    //initialize variables to split insert
    Node* LHSchild = nullptr;
    Node* RHSchild = nullptr;
    string MIDchild = "";

    //base case
    if(curr->large == "") {
        return;
    }

    //check for duplicates
    if(newStr == curr->small || newStr == curr->large){ 
        throw runtime_error("string already exists in tree");
    }

    //if new string is smaller than both string in curr node
    if(newStr < curr->small){  
        //insert new string as left child
        LHSchild = new Node(newStr);
        //set right child to curr node large
        RHSchild = new Node(curr->large);
        //set middle child to curr node small
        MIDchild = curr->small;  
    }

    //if new string is greater than both strings in curr node
    if(newStr > curr->large){ 
        //set left child as curr node small
        LHSchild = new Node(curr->small);
        //set middle child as curr node large
        MIDchild = curr->large;
        //insert new string as right child
        RHSchild = new Node(newStr);
    }

    //if new string is in between small and large
    else{ 
        //set left child as curr node small
        LHSchild = new Node(curr->small);
        //insert new string as middle child
        MIDchild = newStr;
        //set right child as curr node large
        RHSchild = new Node(curr->large);
    }

    //set as empty string to split
    curr->large = "";
    //decrement count
    --curr->count;

    //if not at root or check of node has parent
    if(curr->parent != nullptr){  
        //promote middle child to parent node large
        curr->parent->large = MIDchild;
        //increment parent node count
        ++curr->parent->count;
        //place left child as parent node middle
        curr->parent->middle = LHSchild;
        LHSchild->parent = curr->parent;
        curr->parent->right = RHSchild;
        RHSchild->parent = curr->parent;
    }
    else{ 
        //promote middle child to be parent of LHS and RHS children
        curr->small = MIDchild;
        curr->left = LHSchild;
        curr->right = RHSchild;
        LHSchild->parent = curr;
        RHSchild->parent = curr;
    }

 

}

void Tree::preOrder( ) const {
    //call for recursive helper
    preOrder(root);
    cout << endl;
}

void Tree::preOrder(Node* node ) const {
    //check if empty
    if (node == nullptr) {
        return;
    }

    //if curr node only has one key
    if (node->count == 1) {
        //output
        cout << node->small << ", ";
        //recursive call
        preOrder(node->left);
        preOrder(node->right);
    }

    //if curr node has two keys
    if (node->count == 2) { 
        //output
        cout << node->small << ", ";
        //recursive call
        preOrder(node->left);
        //output
        cout << node->large << ", ";
        //recursive call
        preOrder(node->middle);
        preOrder(node->right);
    }

}

void Tree::inOrder( ) const {
    //call for recursive helper
    inOrder(root);
    cout << endl;
}

void Tree::inOrder(Node* node ) const {
    //check if empty
    if (node == nullptr) {
        return;
    }

    //if curr node has one key
    if (node->count == 1) {
        //output + recursive calls
        inOrder(node->left);
        cout << node->small << ", ";
        inOrder(node->right);
    }

    //if curr node has two keys
    if (node->count == 2) {
        //output + recursive calls
        inOrder(node->left);
        cout << node->small << ", ";
        inOrder(node->middle);
        cout << node->large << ", ";
        inOrder(node->right);
    }
    

}

void Tree::postOrder( ) const {
    //call for recursive helper
    postOrder(root);
    cout << endl;
}

void Tree::postOrder(Node* node ) const {
    //check if emepty
    if (node == nullptr) {
        return;
    }

    //if curr node has one key
    if(node->count == 1) {
        //output + recursive call
        postOrder(node->left);
        postOrder(node->right);
        cout << node->small << ", ";
    }

    //if curr node has two keys
    if(node->count == 2) { 
        //output + recursive calls
        postOrder(node->left);
        postOrder(node->middle);
        cout << node->small << ", ";
        postOrder(node->right);
        cout << node->large << ", ";
    }
 
}

void Tree::remove(const string& removing) {
    remove(root, removing);
    return;
}

void Tree::remove(Node* node, const string& removing) {
    
    //if tree empty, throw error
    if (node == nullptr) {
        throw runtime_error ("calling remove on empty tree");
    }

    //if string not in tree
    if (!search(removing)) {
        return;
    }

    //set node equal to the node of the string needing to be removed
    node = searchNode(node, removing);

    //if removing string is at root
    if (node->parent == nullptr) {
        //if root is lead
        if (node->left == nullptr && node->right == nullptr) {
            //if root only has 1 key
            if (node->count == 1) {
                //delete root
                delete node;
                //root is null
                root = nullptr;
            }
            //if root has more than one key
            else {
                //if root's small string is removing string
                if (node->small == removing){
                    //replace current small with current large
                    node->small = node->large;
                    node->large = "";
                    //decrement count
                    --node->count;
                }
                //if large string is removing string
                else if (node->large == removing){
                    //delete large string
                    node->large = "";
                    --node->count;
                }   
            }
        }



    }

    else{ //if removing string is not at root
            //if removing node only has one key
            if(node->count == 1){ 
                //create new node to replace nodes
                Node* replace = node->parent;
                //if removing string is at right of parent node
                if(replace->right == node){  
                    //replace nodes
                    replace->large = replace->small;
                    replace->small = replace->left->small;
                }
                //if removing string is ar left of parent node
                else if (replace->left == node){ 
                    //replace node
                    replace->large = replace->right->small;
                }
                //increment parent count
                ++replace->count;
                //delete children
                delete replace->left;
                delete replace->right;
                //set children as null
                replace->left = nullptr;
                replace->right = nullptr;
            }
            //if removing node has more than one key
            else { 
                //if removing string is small key then replace with large key
                if(node->small == removing){ 
                    node->small = node->large;
                }
                //decrement
                --node->count;
                node->large = "";         
            }
        }

}

bool Tree::search (const string &searching) const {
    //call for recursive helper
    return search(root, searching);
}

bool Tree::search (Node* curr, const string& searching) const {
    //if tree empty, return false
    if (curr == nullptr) {
        return false;
    }

    //if search key found, return true
    if(curr->small == searching || curr->large == searching) {
        return true;
    }

    //if search key is smaller than curr small
    if (searching < curr->small) {
        //call recursive function for LHS
        return search(curr->left, searching);
    }

    //if curr has multiple keys and is in between small and large keys
    if (curr->count == 2 && searching < curr->large) {
        //recursive call for middle
        return search(curr->middle, searching);
    }

    //else, recursive call for RHS
    else {
        return search(curr->right, searching);
    }

    return false;

}

Node* Tree::searchNode(Node* curr, const string &searching) {
    //if tree empty
    if (curr == nullptr) {
        throw runtime_error ("empty");
    }

    //if string is found, return node
    if(curr->small == searching || curr->large == searching) {
        return curr;
    }

    //if search key is smaller than curr small
    if (searching < curr->small) {
        return searchNode(curr->left, searching);
    }

    //if curr has multiple keys and is in between small and large keys
    if (curr->count == 2 && searching < curr->large) {
        return searchNode(curr->middle, searching);
    }

    //else, recursive call for RHS
    else {
        return searchNode(curr->right, searching);
    }

    
}