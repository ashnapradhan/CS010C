#pragma once
// PROFPAT: If you noticed, I included this in main.cpp as well.  There is a concept
// PROFPAT: called "include what you use"  Since we use exceptions in this header
// PROFPAT: file, we should include <stdexcept> here too
#include <stdexcept>

// It is generally a bad idea to put 'using namespace std;' in a .h file
// It is almost as bad to do this... it is better to just use std::overflow_error
// error when you need it in an include so it is clear where it came from
using std::overflow_error;
using std::runtime_error;
using std::underflow_error;

// PROFPAT: template<typename T> is the line that makes this a recipe for creating
// PROFPAT: types. The tests in main.cpp will make them with ints for some tests
// PROFPAT: and strings for others.

// NOTE: Most styles prefer this to be called Stack instead of stack (using
// NOTE: a lead capital letter).  But zybooks expect 'stack' so we leave it
// NOTE: this way
template<typename T>
class stack {
  // PROFPAT: We can do the MAX_SIZE thing in a couple of ways.  Pick one
  // PROFPAT: A -BAD- way to do this is to just use 20 everywhere -- don't do that!
  //
  // PROFPAT: We can use a 'constexpr' (constant expression).  Very modern, very safe
  // PROFPAT: BUT... it is only available with C++11 and beyond
  // static constexpr unsigned MAX_SIZE = 20;
  //
  // PROFPAT: We can use a #define to create a macro, but this has effects outside
  // PROFPAT: this file.  Note: the parens are a good idea for numbers
  // #define MAX_SIZE (20)
  
  // PROFPAT: Obviously this must be replaced by your implementation.  Zybooks
  // PROFPAT: suggests using data (an array) and size.  DO NOT USE vector<T> here!!!!
  static const unsigned MAX_SIZE = 20;
  T dataArr[MAX_SIZE];
  int size; 
  T junk;
public:
  //constructor
  stack() : size(0){}

  // push(T val): inserts a new element (val) of type T (T could be integer or string)
  // into the data. If the data array is full, this function should throw an overflow_error
  // exception with error message "Called push on full stack.".
  void push(const T& value) { //push function that can take in any value data type
    if (size == MAX_SIZE) { //check if there will be overflow
        throw overflow_error("Called push on full stack."); // throw errpr
    }
    dataArr[++size] = value; //else, increment size and place value at end
  }

  // empty(): returns true if the stack is empty otherwise it returns false.
  bool empty() const { 
    return size == 0; // return true if size == 0
  }

  // pop(): removes the last element from data. If the data array is empty, this function
  // should throw an outofrange exception with error message "Called pop on empty stack.".
  void pop() {
    if (empty()) { //check if empty
      throw std::out_of_range("Called pop on empty stack."); // throw error if called pop on empty stack
    }
    --size; //else, decrement size + remove last element
  }

  // pop_two(): removes the last two elements from data. If the data array is empty or is
  // of size 1, this function should throw an out_of_range exception. If empty then the error
  void pop_two() {
    if (empty()) { //check if empty
      throw std::out_of_range("Called pop_two on empty stack."); //throw error if pop two called on empty stack
    }
    if (size == 1) { //check if only has one element
      throw std::out_of_range("Called pop_two on a stack of size 1."); // throw error if pop two called on size of 1
    }
    size -= 2; //else, decrement size by 2 + remove last 2 elements

  }

  // top(): returns the top element of stack (last inserted element). If stack is empty,
  T& top() { 
    if (empty()) { //check if empty
      throw underflow_error("Called top on empty stack."); //if empty, throw underflow error
    }

    return dataArr[size]; //else, return last inserted element
  }

  const T& top() const {
    if (empty()) { //check if empty
        throw underflow_error("Called top on empty stack."); //if empty, throw underflow error
    }

    return dataArr[size]; //else, return last inserted element
  }
};
