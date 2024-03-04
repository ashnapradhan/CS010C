// PROFPAT: by convention, we sort the include by name here
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

// ZYBOOKS: You are given a function that creates a vector of
// ZYBOOKS: characters with random size. You just need to put the
// ZYBOOKS: following piece of code in your main.cpp file as is:
vector<char> createVector() {
  int vecSize = rand() % 26;
  char c = 'a';
  vector<char> vals;
  for(int i = 0; i < vecSize; i++)
    {
      vals.push_back(c);
      c++;
    }
  return vals;
}


template <typename T> // declare template
unsigned min_index(const vector<T> &vals, unsigned index) {
  unsigned result = index; // declare minimum value index 

  for (unsigned i = index; i < vals.size(); ++i) { // go through entire vector
    if ((vals[i] <= vals[result])) { // if element is <= next element
      result = i; // change result if min value is found
    }
    //cout << vals.at(i) << endl; 
  }
  return result; // return index of min value
}


template <typename T> // define template T
void selection_sort(vector<T> &vals) {
  for (unsigned int i = 0; i < vals.size(); ++i) { // go through entire vector
    unsigned minIndex = min_index(vals, i); // get min_index of elements until index i
    swap(vals[i], vals[minIndex]); // swap elements with index of min value
  }
}


template <typename T> // declare template
T getElement(const vector<T>& vals, int index) { 
  int size = vals.size(); // to compare both as ints
  // if index is out of range 
  try { // try to find out of range index
    if (index < 0 || index > size) { // check index
    // throw error
    throw out_of_range("Error: Index is out of range.");
    }
  }
  catch (const out_of_range& excpt) { // catch  out of range error
    cout << "Error: Index is out of range." << endl;
  }
  // else, return correct element
  return vals[index];
}

// PROFPAT: Make this and then run with % ./a.out < test.txt
// ZYBOOKS: You should write up a try catch block in main function 
// ZYBOOKS: so that when the index is out of the range of the
// ZYBOOKS: vector, the "std::outofrange" exception will be caught 
// ZYBOOKS: by the catch(const std::outofrange& excpt).
// ZYBOOKS: Once the exception is caught, it
// ZYBOOKS: should output "out of range exception occured" followed by a
// ZYBOOKS: new line.
// ZYBOOKS: 
// ZYBOOKS: You should come up with test harnesses to test your
// ZYBOOKS: selection_sort function.
int main() {
  // Seeding the random number generator so we get a different
  // run every time.
  srand(time(0));

  // Fill in a vector of some random size with some random
  // characters
  vector<char> vals = createVector();
  int numOfRuns = 10;
  while(--numOfRuns >= 0){
    cout << "Enter a number: " << endl;
    // PROFPAT: Just because zybooks doesn't think it is important
    // PROFPAT: to check inputs doesn't mean you should skip it
    int index;
    if (not (cin >> index)) {
      throw runtime_error("could not read the index");
    }

    // PROFPAT: We will use a try/catch block here to "protect"
    // PROFPAT: the call to getElement() otherwise the program
    // PROFPAT: will terminate on the throw.  Remember!  The
    // PROFPAT: throw happens where we detect the issue.  The
    // PROFPAT: try/catch occurs where we want to handle it!!!!
    char curChar = getElement(vals,index);
    cout << "Element located at " << index << ": is " << curChar << endl;
  }

  // PROFPAT:  You should test selection sort here!!!!
  return 0;
}
