#include "IntList.h"

#include <iostream>
#include <exception>

using namespace std;

// This is just for the throws during the
// development phase... it is a turd once
// you remove all the HERE's
#define STRINGIZE(x) #x
#define STR(x) STRINGIZE(x)
#define HERE ("Broken at\n" __FILE__ ":" STR(__LINE__) ": broken")

#include <iostream>
ostream & operator<<(ostream &out, const IntList &rhs) {
  //get first node
  IntNode* current = rhs.dummyHead.next;
  //while have not reached end
  while (current != &rhs.dummyTail) {
    //output data
    out << current->data;
    //while not at end, output space
    if (current->next != &rhs.dummyTail) {
      out << " ";
    }
    //move to next node
    current = current->next;
  }
  return out;
}

IntList::~IntList() {
  
  //use pop_front to destruct
  while (!empty()) {
    pop_front();
  }

}

void IntList::push_front(int value) {
  //get the first node
  //IntNode* firstVal = dummyHead.next;
  //create new node for the value
  IntNode* newNode = new IntNode(value);

  //set the new node's previous pointer to the head
  newNode->prev = &dummyHead;
  //set the new node's next pointer to the head's next node (original node 1)
  newNode->next = dummyHead.next;
  //set the head's next to the new node
  dummyHead.next = newNode;

}

void IntList::pop_front() {
  //check if empty, runtime error check
  if (empty()) {
    throw runtime_error("Error: List is empty.");
  }

  else {
    //get the first node
    IntNode* deleteFront = dummyHead.next;
    //set the head's next pointer to the next node of the first node (second node)
    dummyHead.next = deleteFront->next;
    //now set the second node's previous pointer to the head
    deleteFront->next->prev = &dummyHead;
    //delete the original first node
    delete deleteFront;

  }


}

void IntList::push_back(int value) {
  //create new node for the value
  IntNode* addValue = new IntNode(value);
  //set the previous node of the new node to the tail's previous node
  addValue->prev = dummyTail.prev;
  //now set the new node's next pointer to the tail
  addValue->next = &dummyTail;
  //now set the next pointer of the tail's previous pointer to the new node
  dummyTail.prev->next = addValue;
  //now set tail's previous to the new node
  dummyTail.prev = addValue;

}

void IntList::pop_back() {
  //check if empty, runtime error check
  if (empty()) {
    throw runtime_error("Error: List is empty.");
  }

  //get last node
  IntNode* lastNode = dummyTail.prev;
  //set the tail's previous to the previous of the last node
  dummyTail.prev = lastNode->prev;
  //now set the previous of the last node pointing to the tail
  lastNode->prev->next = &dummyTail;
  //delete the correct node
  delete lastNode;

}

bool IntList::empty() const {
  //if the tail is after the head (empty)
  if (dummyHead.next == &dummyTail) {
    return true;
  } else {
    return false;
  }

}

void IntList::printReverse() const {
  //start from the end of the list
  IntNode*current = dummyTail.prev;

  //"while not yet reached the front"
  while(current != &dummyHead) {
    //output data
    cout << current->data;
    //if we have reached the head
    if(current->prev != &dummyHead) {
      cout << " ";
    }
    //move to previous node and work backwards
    current = current->prev;
  }

}

